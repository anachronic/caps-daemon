# caps-daemon

Caps daemon is a simple daemon for X intended to be used alongside
[dwmblocks](https://github.com/torrinfail/dwmblocks) and dwm patched with
[statuscmd](https://dwm.suckless.org/patches/statuscmd/).

By using this daemon you can send signals to your `dwmblocks` process and tell
it your caps lock is either activated or not activated, this stops having to be
polling for caps events every 1 second or so.

I tested this tool with Valgrind to check for memory leaks and should be ok.

If you want to use, you might want to fork it to change the signal number that
is sent to dwmblocks.

## Roadmap

- [ ] Make a makefile (jeez I'm lazy)
- [ ] Make an install script
