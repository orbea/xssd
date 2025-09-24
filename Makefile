.POSIX:

NAME = xssd

PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

CC = cc
PKG_CONFIG = pkg-config

CFLAGS = -O2
FLAGS = -std=c89 -Wall -Wextra -ansi -pedantic

TARGET = sdl2

include mk/$(TARGET).mk

CFLAGS_SDL = `$(PKG_CONFIG) --cflags $(TARGET)`
LIBS_SDL = `$(PKG_CONFIG) --libs $(TARGET)`

INCLUDES = $(CFLAGS_SDL)
LIBS = $(LIBS_SDL)

.PHONY: all install install-strip uninstall clean

all: $(NAME)

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $? $(FLAGS) $(DEFINES) $(INCLUDES) $(LIBS) $(LDFLAGS)

install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(NAME) $(DESTDIR)$(BINDIR)

install-strip: install
	strip $(DESTDIR)$(BINDIR)/$(NAME)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(NAME)

clean:
	rm -f $(NAME)
