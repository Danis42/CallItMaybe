#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int urandom_roll(void) {
    unsigned char byte;
    FILE *f = fopen("/dev/urandom", "rb");
    if (!f) return 50;
    fread(&byte, 1, 1, f);
    fclose(f);
    return byte % 100;
}

int main(int argc, char *argv[]) {
    int fail_chance = 50;
    int cmd_start = 1;

    if (argc >= 2 && strcmp(argv[1], "-c") == 0) {
        if (argc >= 3) {
            char *end;
            long val = strtol(argv[2], &end, 10);
            if (*end == '\0' && val >= 0 && val <= 100)
                fail_chance = (int)val;
        }
        cmd_start = 3;
    }

    int roll = urandom_roll();

    /* pipe mode */
    if (cmd_start >= argc) {
        if (roll < fail_chance) return 0;
        char buf[4096];
        size_t n;
        while ((n = fread(buf, 1, sizeof(buf), stdin)) > 0)
            fwrite(buf, 1, n, stdout);
        return 0;
    }

    /* command mode */
    if (roll < fail_chance) return 0;
    execvp(argv[cmd_start], &argv[cmd_start]);
    perror("maybe");
    return 127;
}
