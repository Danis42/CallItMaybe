CC = gcc
CFLAGS = -O2 -Wall
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

maybe: maybe.c
	$(CC) $(CFLAGS) -o maybe maybe.c

install: maybe
	install -Dm755 maybe $(DESTDIR)$(BINDIR)/maybe

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/maybe

clean:
	rm -f maybe

.PHONY: install uninstall clean
