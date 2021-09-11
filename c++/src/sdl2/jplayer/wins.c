#include <stdio.h>

#include "include/wins.h"
#include "include/vars.h"
#include "include/jsnd.h"
#include "include/snd.h"
#include <askfile.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define DEBUG
/* Notice:
 * every function that starts with 'quit' must be void ?()
 * They will be called by atexit
 */



/* first section for winrs
 * include init and quit, because it's a global variables struct
 */
void quit_winrs() {
	// Notice that we can't free the surface get from the window
	// Or it could cause segmentation fault
	// And it's better to destroy renderer before window
	SDL_DestroyRenderer(winrs.ren);
	SDL_DestroyWindow(winrs.win);
}

void init_winrs() {
	winrs.win = NULL;
	winrs.sur = NULL;
	winrs.ren = NULL;

	winrs.win = SDL_CreateWindow(title, // The title of the window
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // the position of the window
			width, height, // As it name means
			SDL_WINDOW_SHOWN); // and it's flags
	if (winrs.win == NULL) {
		fprintf(stderr, "Cound not create sdl window: %s\n", SDL_GetError());
		exit(1);
	}

	// Create renderer, the last flag means update with the screen
	winrs.ren = SDL_CreateRenderer(winrs.win, -1, SDL_RENDERER_PRESENTVSYNC);
	if (winrs.ren == NULL) {
		fprintf(stderr, "Could not create window renderer: %s\n", SDL_GetError());
		exit(1);
	}

	// I don't know why i must get surface after renderer created
	// Or it would cause segmentation fault when using SDL_FillRect
	// that's serious! warning
	winrs.sur = SDL_GetWindowSurface(winrs.win);
	if (winrs.sur == NULL) {
		fprintf(stderr, "Could not get win surface: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(quit_winrs);
}

/* second section for imgs
 * consts and vars in vars.h
 * include init, quit and fill.
 */

void quit_imgs() {
	SDL_FreeSurface(imgs.start);
	SDL_FreeSurface(imgs.stop);
}

void init_imgs() {
	mus.stopped = 1;
	imgs.down = 0;
	imgs.stop = SDL_LoadBMP(imgs_stop_fn);
	imgs.start = SDL_LoadBMP(imgs_start_fn);
	if (imgs.start == NULL || imgs.stop == NULL) {
		if (imgs.start == NULL) printf("Start missing\n");
		else printf("stop missing\n");
		check(1, "Could not load images: %s\n");
		exit(1);
	}
	atexit(quit_imgs);
}

void fill_imgs() {
	SDL_Surface * img;
	if (mus.stopped == 1) { // stopped
		img = imgs.start;
	} else { // started
		img = imgs.stop;
	}
	fillRect(&imgs_place, 0);
	if (check(SDL_BlitSurface(img, NULL, winrs.sur, &imgs_place), "Could not blit surface: %s\n")) exit(1);
}

/* section 4
 * for ttf fonts need
 */

void init_fonts() {
	if (check(TTF_Init(), "Could not load turetypefont lib: %s\n")) exit(1);
	fonts.f18 = TTF_OpenFont("fonts/font.ttf", 18);
	fonts.f15 = TTF_OpenFont("fonts/font.ttf", 15);
	fonts.f12 = TTF_OpenFont("fonts/font.ttf", 12);
	if (fonts.f18 == NULL || fonts.f15 == NULL || fonts.f12 == NULL) {
		check(1, "Could not load any font: %s\n");
		exit(1);
	}
}

void quit_fonts() {
	TTF_CloseFont(fonts.f18);
	TTF_CloseFont(fonts.f15);
	TTF_CloseFont(fonts.f12);
	TTF_Quit();
}

/* section 5
 * for showing time string on the top
 * it should be easy
 */

void init_times() {
	char * times = get_ntimes();
	// if (strcmp(times, _old_times) == 0)
	// 	return;
	_old_times = times;
	SDL_Surface * sur = renderText(fonts.f15, times);
	fillRect(&times_place, 0);
	SDL_BlitSurface(sur, NULL, winrs.sur, &times_place);
	SDL_FreeSurface(sur);

	_update_times_id = SDL_AddTimer(1000 / 24, _update_times, NULL);
	// printf("add times timer\n");
	atexit(quit_times);
}

void quit_times() {
	SDL_RemoveTimer(_update_times_id);
}

SDL_Surface * renderText(TTF_Font * font, const char * s) {
	return TTF_RenderUTF8_Blended(font, s, color);
}

Uint32 _update_times(Uint32 interval, void * param) {
	if (state() == -1) return interval;
	char * times = get_ntimes();
	if (strcmp(times, _old_times) == 0)
	 	return interval;
	free(_old_times);
	_old_times = times;
	SDL_Surface * sur = renderText(fonts.f15, times);
	fillRect(&times_place, 0);
	SDL_BlitSurface(sur, NULL, winrs.sur, &times_place);
	SDL_FreeSurface(sur);
	return interval;
}

/* section 6
 * Just for scroller
 * can set the music time and show the position
 */

void init_scl() {
	scl.back.x = (scl.back.y = 25);
	scl.back.w = 250; scl.back.h = 5;

	scl.front.x = 25 - 8; scl.front.y = 20;
	scl.front.w = 15; scl.front.h = 15;

	scl.left.y = 25; scl.left.x = 25;
	scl.left.w = 1; scl.left.h = 5;


	_update_scl_id = SDL_AddTimer(100 / 24, _update_scl, NULL);
	atexit(quit_scl);

	change_scl(0);
}

void quit_scl() {
	SDL_RemoveTimer(_update_scl_id);
}

Uint32 _update_scl(Uint32 interval, void * param) {
	if (!mus.stopped) {
		if (get_ntime() >= get_time()) {
			restart();
			return interval;
		}
		scl.x_perc = get_ntime() / (double)(get_time());
		fill_scl();
	}
	return interval;
}

void change_scl(int x) {
	if (25 > x) x = 25;
	else if (x > 275) x = 275;
	scl.x_perc =  (double)(x - 25) / 250;
	// if (x == 25) scl.x_perc = 0;
	// printf("change scl x = %d\n", x);
	fill_scl();
}

void update_scl() {
	int mt = get_time();
	int nt = mt * scl.x_perc;
	set_ntime(nt);
	// printf("update scl\n");
}

void fill_scl() {
	int x = scl.x_perc * 250;

	scl.front.x = x + 25 - 8;
	scl.left.w = x;

	// printf("Fill scl! x = %d\n", x);
	// printf("scl.left.w = %d\n", x);
	fillRect(&scl_place, 0);

	fillRect(&scl.back, SDL_MapRGB(winrs.sur->format, 0, 175, 175));
	fillRect(&scl.left, SDL_MapRGB(winrs.sur->format, 0, 255, 255)); // segmentfault
	fillRect(&scl.front, SDL_MapRGB(winrs.sur->format, 0, 0, 255));
}

/* section seven
 * showing filename on the top
 * and the button to select a file
 */

int set_filename(const char * fn) {
	SDL_Surface * sur = renderText(fonts.f18, fn);
	fillRect(&fn_place, 0);
	if(SDL_BlitSurface(sur, NULL, winrs.sur, &fn_place) != 0) return 1;
	return 0;
}

void init_slt() {
	slt.down = 0;
	slt.sur = renderText(fonts.f15, "Select  File");
	int width = 70;
	slt.border.x = 24; slt.border.y = 79;
	slt.border.w = width + 2; slt.border.h = 22;

	slt.inside.x = 25; slt.inside.y = 80;
	slt.inside.w = width; slt.inside.h = 20;

	fillRect(&slt.border, SDL_MapRGB(winrs.sur->format, 255, 255, 255));
	fillRect(&slt.inside, 0);
	slt.inside.x += 2;
	SDL_BlitSurface(slt.sur, NULL, winrs.sur, &slt.inside);

	atexit(quit_slt);
}

void quit_slt() {
	SDL_FreeSurface(slt.sur);
}

/* second last section
 * for no topic functions
 */

void new_media() {
	const char * fn = askfile();
	if (!fn) {
		check(1, "No file input");
		return;
	}
	set_filename(fn);
	load_media(fn);
}

/* last section
 * for other functions
 * they have no topic but they are of great importance
 */

int fillRect(SDL_Rect * rect, Uint32 color) {
	if (SDL_FillRect(winrs.sur, rect, color) != 0) {
		check(1, "Could not fill rect: %s\n");
		exit(1);
	}
	return 0;
}

int check(int result, const char * s) {
	// This is a function to check if there is any error
	// if there's, print the error and then quit
	if (result != 0) {
		const char * e = SDL_GetError();
		char * emsg = (char *)malloc(sizeof(char) * (strlen(e) + strlen(s)));
		sprintf(emsg, s, e);
		if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Jplayer Error", emsg, NULL) != 0) {
			fprintf(stderr, emsg);
			fprintf(stderr, "\n");
		}
		return 1;
	}
	return 0;
}

int checkClick(SDL_Rect rect, SDL_Event e) {
	int x = e.button.x, y = e.button.y;
	if (x > rect.x && rect.x + rect.w > x && y > rect.y && rect.y + rect.h > y) {
		return 1;
	}
	return 0;
}


Uint32 _update_ren(Uint32 interval, void * param) {
	SDL_Texture * text = SDL_CreateTextureFromSurface(winrs.ren, winrs.sur);
	// when test, we know we can clear the renderer whenever we want
	// even if it's empty
	SDL_RenderClear(winrs.ren);
	// When the last two args are both null,
	// that means we copy the whole texture to fill the whole screen
	SDL_RenderCopy(winrs.ren, text, NULL, NULL);
	// update the screen
	SDL_RenderPresent(winrs.ren);
	// Destroy the texture to save more splace
	SDL_DestroyTexture(text);
	return interval;
}

void mainloop() {
	init_winrs();
	init_imgs();
	init_fonts();
	init_times();
	init_scl();
	init_slt();

	// Add the timer to update (1000 / 24 means the win would be 24\fps)
	_update_ren_id = SDL_AddTimer(1000 / 24, _update_ren, NULL);

	// fill imgs
	fill_imgs();
	
	printf("Loop start\n");

	// test first
	// load_media("sound/2.mp3");
	// printf("music time: %d\n", get_time());

	SDL_Event e;
	while (1) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_MOUSEBUTTONUP:
					if (checkClick(imgs_place, e) && imgs.down == 1) {
						if (state() == -1) {
							no_mus_e();
							break;
						}
						if (mus.stopped) { // to start
							if (start()) stop();
						} else { // to stop
							stop();
						}
						fill_imgs();
						imgs.down = 0;
					} else if (scl.down) {
						if (scl.down == 2) start();
						scl.down = 0;
						update_scl();
						fill_imgs();
					} else if (checkClick(slt.inside, e) && slt.down == 1) {
						slt.down = 0;
						new_media();
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (checkClick(imgs_place, e)) {
					       	imgs.down = 1;
					} else if (checkClick(scl.front, e)) {
						scl.down = 1;
						if (state() == 1) {
							scl.down = 2;
						}
						stop();
						fill_imgs();
					} else if (checkClick(slt.inside, e)) {
						slt.down = 1;
					}
					break;
				case SDL_MOUSEMOTION:
					if (scl.down) {
						change_scl(e.button.x);
					}
					break;
				case SDL_QUIT:
					goto __quit;
			}
		}
		SDL_Delay(20);
	}
__quit:
	SDL_RemoveTimer(_update_ren_id);
}
