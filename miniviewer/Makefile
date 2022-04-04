PKGS=sdl2 SDL2_image
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb `pkg-config --cflags $(PKGS)`
LIBS=`pkg-config --libs $(PKGS)` -lm

all: miniviewer

miniviewer: main.o
	$(CC) $(CFLAGS) -o miniviewer main.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o $(LIBS)
