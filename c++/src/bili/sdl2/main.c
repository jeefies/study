#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define LINE_WIDTH 2
#define FPS 1000/24
#define width 360
#define height 640

#define RectN 4

struct {
	SDL_Window * win;
	SDL_Renderer * ren;
	SDL_Surface * sur;
} winrs;

SDL_TimerID _update_ren_id;

struct {
	int ys[RectN];
	int ps[RectN];
	int cs[RectN];
} yps;

SDL_Surface * scr_sur = NULL;

int speed;
int failed = 0;
int round = 0;

int check(int res, const char * ctx) {
	if (res != 0) {
		fprintf(stderr, ctx);
		fprintf(stderr, ": %s\n", SDL_GetError());
		return 1;
	}
	return 0;
}

int check_p(void * p, const char * ctx) {
	if (p == NULL) {
		fprintf(stderr, ctx);
		fprintf(stderr, ": %s\n", SDL_GetError());
	}
}

int fillRect(SDL_Rect * rect, Uint32 color) {
	if (check(SDL_FillRect(winrs.sur, rect, color), "Could not fill rect")) exit(1);
	return 0;
}

int checkClick(SDL_rect rect, SDL_Event e) {
	int x = e.button.x;
	int y = e.button.y;
	if (x > rect.x && rect.x + rect.w > x && y > rect.y && rect.y + rect.h > y) {
		return 1;
	}
	return 0;
}

Uint32 _update_ren(Uint32 interval, void * param) {
	SDL_RenderClear(winrs.ren);

	SDL_Texture * text = SDL_CreateTextureFromSurface(winrs.ren, winrs.sur);
	SDL_RenderCopy(winrs, text, NULL, NULL);
	SDL_DestroyTexture(text);

	SDL_RenderPresent(winrs.ren);
	return interval;
}

SDL_Surface * renderText(TTF_Font * font, const char * ctx) {
	SDL_Color color = {255, 255, 255};
	return TTF_RenderText_Blended(font, ctx, color);
}

void applySurface(SDL_Rect * to, SDL_Surface * Surface) {
	check(SDL_BlitSurface(Surface, NULL, winrs.sur, to), "Could not apply surface");
}
