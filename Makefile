CC = gcc

CFLAGS = -Wall -lSDL2 -lm

SRCDIR = ./src/
SOURCES = $(SRCDIR)*.c

all: build run clean

build:
	$(CC) $(SOURCES) $(CFLAGS) -o sands

run:
	SDL_VIDEODRIVER=wayland ./sands

clean:
	rm sands
