# CallItMaybe

Run a command by chance.

```
maybe <cmd>         run cmd with 50% chance
maybe maybe <cmd>   run cmd with random chance (10–90%)
maybe -c <N> <cmd>  run cmd with N% chance (0–100)
<cmd> | maybe       pass stdin to stdout with 50% chance
```

## Install (current user)

```sh
git clone https://github.com/Danis42/CallItMaybe
cd CallItMaybe
make
cp maybe ~/.local/bin/maybe
```

Make sure `~/.local/bin` is in your `PATH`.

## Install system-wide

```sh
git clone https://github.com/Danis42/CallItMaybe
cd CallItMaybe
make
sudo make install        # installs to /usr/local/bin
```

Or on Arch Linux via the AUR:

```sh
makepkg -si
```
