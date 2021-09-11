#include <stdio.h>
#include <stdlib.h>

#include "include/jplayer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

void quit() {
	Mix_Quit();
	SDL_Quit();
	printf("Quit all\n");
}

int main(int argc, char * argv[]) {
	// Init SDL and check if init error
	if (SDL_Init(SDL_INIT) < 0) {
		fprintf(stderr, "Could not init sdl: %s\n", SDL_GetError());
		exit(1);
	}

	// Init subsystem(sdl_mixer) and process the error if exists
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, samplesize) < 0) {
		fprintf(stderr, "Could not init sdl_mixer: %s\n", SDL_GetError());
		exit(1);
	}

	mainloop();

	// these quit function will call at last
	atexit(quit);

	return 0;
}
