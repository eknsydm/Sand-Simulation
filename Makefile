CC = gcc

CFLAGS = -Wall -lSDL2 -lm

SRCDIR = ./src/
SOURCES = $(SRCDIR)*.c

all: sands run clean

sands:
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	SDL_VIDEODRIVER=wayland ./sands

clean:
	rm sands
