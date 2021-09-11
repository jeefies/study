CFLAGS = -g -Wall

all: main.c
	gcc main.c -o play.exe `pkg-config SDL2_mixer SDL2_ttf --cflags --libs` $(CFLAGS)
