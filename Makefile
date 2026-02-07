PREFIX ?= /data/data/com.termux/files/usr
CC ?= clang
CFLAGS = -Wall

all: crx-bar

crx-bar: main.c
	$(CC) $(CFLAGS) main.c -o crx-bar

install:
	install -Dm755 crx-bar $(DESTDIR)$(PREFIX)/bin/crx-bar

clean:
	rm -f crx-bar
