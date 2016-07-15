CFLAGS = -Wall -O2 -std=c99
NAME = brclock
FILE = brclock.c
PREFIX = /usr/local

brclock: $(FILE)
	$(CC) -o $(NAME) $(FILE) $(CFLAGS)

install: brclock
	mkdir -p $(DESTDIR)$(PREFIX)/bin/
	cp -f $(NAME) $(DESTDIR)$(PREFIX)/bin/

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(NAME)

clean:
	rm $(NAME)
