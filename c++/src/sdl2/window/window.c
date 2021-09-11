#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>


SDL_Window *window = NULL;
SDL_Surface * surface = NULL;

#ifdef __cplusplus
extern "C" {
#endif

int init();
void quit();

int createScreen(const char* title, int width, int height);
int fillRGB(int red, int green, int blue);

#ifdef __cplusplus
}
#endif

int createScreen(const char* title, int width, int height) {
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!window) {
		printf("Could Not create Screen: %s\n", SDL_GetError());
		return 1;
	}
	surface = SDL_GetWindowSurface(window);
	if (surface == NULL) {
		printf("Could not get surface: %s\n", SDL_GetError());
		return 1;
	}
} 

int fillRGB(int red, int green, int blue) {
	// NULL means fill all
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, red, green, blue));
	SDL_UpdateWindowSurface(window);
	return 0;
}

int init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could Not Init SDL: %s\n", SDL_GetError());
		return 1;
	}
	return 0;
}

void quit() {
	printf("Quit!\n");
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main() {
	if (init() == 1) {
		return 1;
	}
	atexit(quit);

	createScreen("Hello", 200, 100);
	fillRGB(0, 255, 0);

	SDL_Delay(5000);

	return 0;
}
