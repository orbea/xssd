.POSIX:

NAME = scrnsaverdisable-sdl

PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

CC = cc
PKG_CONFIG = pkg-config

CFLAGS = -O2
FLAGS = -std=c89 -Wall -Wextra -ansi -pedantic

CFLAGS_SDL2 = `$(PKG_CONFIG) --cflags sdl2`
LIBS_SDL2 = `$(PKG_CONFIG) --libs sdl2`

INCLUDES = $(CFLAGS_SDL2)
LIBS = $(LIBS_SDL2)

all: $(NAME)

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $? $(FLAGS) $(INCLUDES) $(LIBS) $(LDFLAGS)

install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(NAME) $(DESTDIR)$(BINDIR)/

install-strip: install
	strip $(DESTDIR)$(BINDIR)/$(NAME)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(NAME)

clean:
	rm -f $(NAME)
