#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifdef __cplusplus
extern "C" {
#endif

int init();
void quit();

int createWindow(const char* title, int width, int height);
int createRenderer();
//int createTexture();
int initBackRect(int x, int y, int w, int h);
int initFrontRect(int x, int y, int w, int h);
int initFillRect(int x, int y, int w, int h);
int fillRect(SDL_Rect * rect, int r, int b, int g);

int mainloop();
int mousemotion(SDL_Event e);
int mousedown(SDL_Event e);
int update();

#ifdef __cplusplus
}
#endif

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
SDL_Rect backrect;
SDL_Rect frontrect;
SDL_Rect fillrect;
SDL_Texture* texture = NULL;
int width = 0, height = 0;
int down = 0;
int left, right;

int init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could Not Init SDL: %s\n", SDL_GetError());
		return 1;
	}
	return 0;
}

int createWindow(const char* title, int width, int height) {
	// SDL_CreateWindow(title, x, y, width, height, flags)
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height, SDL_WINDOW_SHOWN); //| SDL_WINDOW_BORDERLESS);
	if (window == NULL) {
		printf("Could Not Create Window: %s\n", SDL_GetError());
		return 1;
	}
	return 0;
}

int createRenderer() {
	if (window == NULL) {
		if (createWindow("Jeefy", 450, 640) == 1) {
			return 1;
		}
	}
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (render == NULL) {
		printf("Could Not Create Renderer: %s\n", SDL_GetError());
		return 1;
	}
	return 0;
}


int initBackRect(int x, int y, int w, int h) {
	backrect.x = x; backrect.y = y; backrect.w = w; backrect.h = h;
	return 0;
}

int initFrontRect(int x, int y, int w, int h) {
	frontrect.x = x; frontrect.y = y; frontrect.w = w; frontrect.h = h;
	return 0;
}

int initFillRect(int x, int y, int w, int h) {
	fillrect.x = x; fillrect.y = y; fillrect.w = w; fillrect.h = h;
	return 0;
}

int fillRect(SDL_Rect * rect, int r, int b, int g) {
	SDL_SetRenderDrawColor(render, r, b, g, 255);
	SDL_RenderFillRect(render, rect);
	return 0;
}

void quit() {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("Quit!\n");
}

int update() {
	SDL_RenderClear(render);
	fillRect(&backrect, 0, 0, 175);
	fillRect(&fillrect, 0, 255, 255);
	fillRect(&frontrect, 0, 175, 175);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);

	SDL_RenderPresent(render);
	return 0;
}

int mousedown(SDL_Event e) {
	int x = e.button.x, y = e.button.y;
	int fx = frontrect.x, fy = frontrect.y;

	if (fx < x && x < fx + 15 && fy < y && y < fy + 15) {
		down = 1;
		printf("Mouse down at %d, %d\n", x, y);
		return 0;
	}
	printf("Click At %d, %d; should be %d, %d\n", x, y, fx, fy); return 1;
}

int mousemotion(SDL_Event e) {
	if (down == 0) {
		return 1;
	}
	int x = e.button.x;
	printf("Mouse move to %d, %d\n", x, e.button.y);
	int w, y;
	if (x < left) {
		w = 0; x = left;
	} else if (x > right) {
		w = right - left; x = right;
	} else {
		w = x - left;
	}
	fillrect.w = w;
	frontrect.x = x - 7;
	update();
	return 0;
}

int mainloop() {
	SDL_Event e;

__loop:
	while (1) {
		while (SDL_PollEvent(&e) == 0) {
			SDL_Delay(20);
		}
		switch (e.type) {
			case SDL_MOUSEBUTTONDOWN:
				if (e.button.button != SDL_BUTTON_LEFT) break;
				mousedown(e); break;
			case SDL_MOUSEMOTION:
				mousemotion(e); break;
			case SDL_MOUSEBUTTONUP:
				printf("mouse up\n");
				down = 0; break;
			case SDL_QUIT:
				goto __quit;
		}
		SDL_Delay(20);
	}
__quit:
	return 0;
}

int main() {
	init();
	atexit(quit);
	if (createWindow("Scroller", 300, 50) == 1)
		return 1;
	if (createRenderer() == 1)
		return 1;
	initBackRect(25, 25, 250, 5);
	left = 25; right = 25 + 250;
	initFrontRect(35,20, 15,  15);
	initFillRect(25, 25, 10,  5);

	update();

	mainloop();

	return 0;
}
