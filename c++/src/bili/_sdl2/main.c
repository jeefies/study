#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define LINE_WIDTH 2
#define FPS 1000/24

#define RectN 4

struct {
	SDL_Window * win;
	SDL_Renderer * ren;
	SDL_Surface  * sur;
} winrs;

SDL_TimerID _update_ren_id;

struct {
	int ys[RectN];
	int ps[RectN];
	int cs[RectN];
} yps;

struct {
	SDL_Surface * scr;
	SDL_Surface * text;
} scr;

int speed = 2;
int failed = 0;
int row = 0;
const int width = 360;
const int height = 640;


int check(int r, const char * emsg) {
	if (r != 0) {
		fprintf(stderr, emsg);
		fprintf(stderr, ":");
		fprintf(stderr, SDL_GetError());
		fprintf(stderr, "\n");
		return 1;
	}
	return 0;
}

int check_p(void * r, const char * emsg) {
	if (!r) {
		fprintf(stderr, emsg);
		fprintf(stderr, ":");
		fprintf(stderr, SDL_GetError());
		fprintf(stderr, "\n");
		return 1;
	}
	return 0;
}

int checkClick(SDL_Rect r, SDL_Event e) {
	int x = e.button.x;
	int y = e.button.y;
	if (x > r.x && r.x + r.w > x && y > r.y && r.y + r.h > y) {
		return 1;
	}
	return 0;
}


int randn(int n) {
	static int init = 0;
    if (!init) {
        srand((unsigned)time(NULL));
        init = 1;
    }
	return rand() % n;
}

void quit() {
	SDL_RemoveTimer(_update_ren_id);
	SDL_DestroyRenderer(winrs.ren);
	SDL_DestroyWindow(winrs.win);
}

int * get_winsize() {
	int * size = (int *)malloc(sizeof(int) * 2);
	SDL_GetWindowSize(winrs.win, &size[0], &size[1]);
	return size;
}

int fillRect(SDL_Rect *rect, Uint32 color) {
	if (check(SDL_FillRect(winrs.sur, rect, color), "Could not fill Rect")) exit(1);
	return 0;
}

void init_scr() {
	TTF_Font * font = TTF_OpenFont("font.ttf", 15); // 20px

	SDL_Color color = {255, 0, 0};
	scr.text = TTF_RenderText_Blended(font, "Score:", color);

	TTF_CloseFont(font);
}

void update_scr() {
	TTF_Font * font = TTF_OpenFont("font.ttf", 15); // 20px
	int w = 50;
	SDL_Rect place = {5, 5, w, 20};
	SDL_Rect splace = {5 + w, 5, w, 20};
	SDL_Color color = {255, 0, 0};

	// fillRect(&place, SDL_MapRGBA(winrs.sur->format, 255, 0, 0, 125));

	SDL_BlitSurface(scr.text, NULL, winrs.sur, &place);

	if (scr.scr) SDL_FreeSurface(scr.scr);
	char s[4];
	sprintf(s, "%03d", row);
	scr.scr = TTF_RenderText_Blended(font, s, color);
	SDL_BlitSurface(scr.scr, NULL, winrs.sur, &splace);

	TTF_CloseFont(font);
}

int start() {
	TTF_Font * font = TTF_OpenFont("font.ttf", 36); // 48px
	yps.cs[0] = yps.cs[1] = yps.cs[2] = yps.cs[3] = 0;

	fillRect(NULL, 0);
	SDL_Color color = {255, 255, 255};
	SDL_Rect rect = {50, height / 2 - 24, 0, 0};

	SDL_Surface * sur = TTF_RenderText_Blended(font, "START GAME", color);
	SDL_BlitSurface(sur, NULL, winrs.sur, &rect);

	SDL_Texture * text = SDL_CreateTextureFromSurface(winrs.ren, sur);
	SDL_RenderCopy(winrs.ren, text, NULL, NULL);

	SDL_FreeSurface(sur);
	SDL_DestroyTexture(text);

	SDL_Event e;

	while (1) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT: exit(1);
				case SDL_MOUSEBUTTONUP:
					       if (checkClick(rect, e)) return 1;
				case SDL_KEYUP:
					       if (e.key.keysym.sym == SDLK_SPACE) return 1;
			}
		}
	}
	TTF_CloseFont(font);
	return 0;
}

int fail() {
	TTF_Font * font = TTF_OpenFont("font.ttf", 36); // 48px

	fillRect(NULL, 0);
	SDL_Color color = {255, 255, 255};
	SDL_Surface * sur = TTF_RenderText_Blended(font, "YOU FAILED", color);
	SDL_Rect rect = {50, height / 2 - 24, 0, 0};
	SDL_BlitSurface(sur, NULL, winrs.sur, &rect);
	SDL_Texture * text = SDL_CreateTextureFromSurface(winrs.ren, sur);
	SDL_RenderCopy(winrs.ren, text, NULL, NULL);

	SDL_Delay(2000);
	return 0;
}

int line(int fd, int pos) {
	// fd 0 for ——, 1 for |
	// pos accords to fd, x if fd is 1, y if fd is 0
	SDL_Rect rect = {0};
	int * ws = get_winsize();
	if (fd == 0) {
		rect.y = pos;
		rect.w = ws[0];
		rect.h = LINE_WIDTH;
	} else {
		rect.x = pos;
		rect.h = ws[1];
		rect.w = LINE_WIDTH;
	}
	free(ws);
	fillRect(&rect, SDL_MapRGB(winrs.sur->format, 255, 255, 255)); // white
	return 0;
}

void update() {
	line(0, height / 4 * 3);
	line(1, width / 4);
	line(1, width / 2);
	line(1, width / 4 * 3);
}

int next_speed(int height) {
	int spd = speed;
	if (spd >= height / 2) return spd;
	while (1) {
		spd++;
		if (height % spd == 0) break;
	}
	return spd;
}

void draw_rects() {
	fillRect(NULL, 0);
	update();
	SDL_Rect r;
	int * size = get_winsize();
	/*
	int rgbs[RectN][3] = {
		{255, 255, 255},
		{200, 200, 200},
		{150, 150, 150},
		{100, 100, 100},
		{50, 50, 50},
	};
	*/
	for (int i = 0; i < RectN; i++) {
		r.x = yps.ps[i] * size[0] / 4;
		r.y = yps.ys[i];
		r.w = size[0] / 4;
		r.h = size[1] / 4;
		if (yps.cs[i]) fillRect(&r, SDL_MapRGBA(winrs.sur->format, 100, 100, 100, 255));
		else fillRect(&r, SDL_MapRGB(winrs.sur->format, 255, 255, 255));
		// printf("Fill Rect %d: x, y, w, h = %d, %d, %d, %d \n", i, r.x, r.y, r.w, r.h);
	}
	free(size);
}

void init_rects() {
	int * size = get_winsize();
	row = 0;
	for (int i = 0; i < RectN; i++) {
		yps.ys[i] = size[1] / 4 * (i - RectN + 1);
__rand:
		yps.ps[i] = randn(4);
		if (i != 0 && yps.ps[i] == yps.ps[i - 1]) goto __rand;
		// printf("rand ps: %d, ys: %d\n", yps.ps[i], yps.ys[i]);
	}
	free(size);
	speed = 5;
	draw_rects();
}

void next_rects() {
	int * size = get_winsize();
	for (int i = 0; i < RectN; i++) {
		if (yps.ys[i] >= size[1] / 4 * 3) {
			yps.ys[i] -= size[1];
			do {
			yps.ps[i] = randn(4);
			} while ( (i != 0 && yps.ps[i] == yps.ps[i - 1]) || yps.ps[0] == yps.ps[RectN - 1]);
			if (yps.cs[i] == 0) { // Failed
				failed = 1;
			}
			yps.cs[i] = 0;

			if (row % 8 == 0){
				// speed = next_speed(size[1] / 4);
				speed += 2;
			}
		}

		yps.ys[i] += speed;
		// printf("yps.ys[%d] add 15 to %d\n", i, yps.ys[i]);
	}
	free(size);
	// printf("\n");
}

Uint32 _update_rect(Uint32 interval, void * param) {
	next_rects();
	draw_rects();
	update_scr();
	return interval;
}

Uint32 _update_ren(Uint32 interval, void * param) {
	SDL_RenderClear(winrs.ren);

	SDL_Texture * text = SDL_CreateTextureFromSurface(winrs.ren, winrs.sur);
	SDL_RenderCopy(winrs.ren, text, NULL, NULL);
	SDL_DestroyTexture(text);

	SDL_RenderPresent(winrs.ren);
	return interval;
}

int check_k(int n) {
	// printf("Check k, n = %d\n", n);
	for (int i = 0; i < RectN; i++) {
		if (yps.ps[i] == n && yps.ys[i] >= height / 2) {
			yps.cs[i] = 1;
			row += 1;
			return 0;
		}
		// printf("p = %d, y = %d, ck = %d\n", yps.ps[i], yps.ys[i], height / 2);
	}
	return 1;
}


int main() {
	if (check(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_EVENTS|SDL_INIT_TIMER), "Could not init sdl")) exit(1);
	if (check(TTF_Init(), "Could not init ttf")) exit(1);
	if (check_p(
				(winrs.win = SDL_CreateWindow("play", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN)),
				"Could not create windw")
			)
		exit(1);
	if (check_p(
				(winrs.ren = SDL_CreateRenderer(winrs.win, -1, SDL_RENDERER_PRESENTVSYNC)),
				 "Could not create renderer")
			)
		exit(1);
	if (check_p(
				(winrs.sur = SDL_GetWindowSurface(winrs.win)),
				 "Could Not get surface"))
		exit(1);

	_update_ren_id= SDL_AddTimer(FPS, _update_ren, NULL);
	while (start()) {

		fillRect(NULL, 0);
		atexit(quit);

		init_rects();
		SDL_TimerID _update_rect_id = SDL_AddTimer(FPS, _update_rect, NULL);

		init_scr();

		update();

		SDL_Event e;
		
		// int ex_l = height / 4 * 2;
		// printf("Ex_l = %d\n", ex_l);

	
		while (1) {
			if (failed) {
				failed = 0;
				break;
			}
			while (SDL_PollEvent(&e)) {
				switch (e.type) {
					case SDL_QUIT:
						goto __quit;
					case SDL_KEYDOWN:
						// printf("ys4 %d %d %d %d\n", yps.ys[0], yps.ys[1], yps.ys[2], yps.ys[3]);
						switch (e.key.keysym.sym) {
							case 'a':
							case 'j':
								if (check_k(0)) goto __fail;
								break;
							case 's':
							case 'k':	
								if (check_k(1)) goto __fail;
								break;
							case 'd':
							case 'l':	
								if (check_k(2)) goto __fail;
								break;
							case 'f':
							case ';':	
								if (check_k(3)) goto __fail;
								break;
						} break;
				}
			}
		}
__fail:
		SDL_RemoveTimer(_update_rect_id);
		SDL_Delay(50);
		fail();
	}

__quit:
	return 0;
}
