#include <stdio.h>   // fopen, fread, fclose, fwrite, perror
#include <stdlib.h>  // strtol
#include <string.h>  // strcmp
#include <unistd.h>  // execvp

// reads one random byte from the OS entropy source
static unsigned char rand_byte(void) {
    unsigned char b;
    FILE *f = fopen("/dev/urandom", "rb");  // open the kernel random device
    if (!f) return 0;                       // if open fails, fall back to 0
    fread(&b, 1, 1, f);                     // read exactly one byte
    fclose(f);                              // close the file
    return b;                               // return the byte
}

int main(int argc, char *argv[]) {
    if (getuid() != geteuid()) {
        fputs("maybe: refusing to run setuid\n", stderr);
        return 1;
    }

    if (argc >= 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        puts("Call it Maybe :) \n"
             "\n"
             "Usage:\n"
             "  maybe <cmd>         run cmd with 50% chance\n"
             "  maybe maybe <cmd>   run cmd with random chance (10-90%)\n"
             "  maybe -c <N> <cmd>  run cmd with N% chance (0-100)\n"
             "  <cmd> | maybe       pass stdin to stdout with 50% chance\n"
             "\n"
             "Exit 0 whether the command runs or not.");
        return 0;
    }

    int threshold = 50;  // default: 50% chance
    int cmd_start = 1;   // index into argv where the real command begins

    if (argc >= 2 && strcmp(argv[1], "maybe") == 0) {       // "maybe" keyword: randomise the threshold
        threshold = 10 + rand_byte() % 81;                  // pick a random threshold between 10 and 90
        cmd_start = 2;                                      // command starts after second "maybe"
    } else if (argc >= 2 && strcmp(argv[1], "-c") == 0) {   // "-c N": explicit threshold
        if (argc >= 3) {                                    // check if something is after "-c"
            char *end;                                      // end of Number
            long val = strtol(argv[2], &end, 10);           // parse the threshold as a base-10 integer
            if (*end == '\0' && val >= 0 && val <= 100)     // check if threshold is between [0, 100]
                threshold = (int)val;                       // use the supplied threshold
        }
        cmd_start = 3;  // real command starts after "-c N"
    }

    int roll = rand_byte() % 100;  // roll a number in [0, 99]

    if (roll < threshold)  // if the roll is below the threshold, do nothing
        return 0;          // skip it - do nothing

    if (cmd_start >= argc) {                                        // no command given - pass-through filter
        char buf[4096];                                             // chunk buffer for stdin data
        size_t n;                                                   // number of bytes read in each chunk
        while ((n = fread(buf, 1, sizeof(buf), stdin)) > 0)         // read stdin until EOF
            fwrite(buf, 1, n, stdout);                              // write each chunk straight to stdout
        return 0;                                                   // done, exit cleanly
    }

    execvp(argv[cmd_start], &argv[cmd_start]);      // replace this process with the requested command
    perror("maybe");                                // only reached if execvp failed
    return 127;                                     // 127 is the conventional "command not found" exit code
}
