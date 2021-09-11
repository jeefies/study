#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifdef _MSC_VER
	#include <io.h>
	#define access _access
#else
	#include <unistd.h>
#endif

#include "askfile.h"

#define key e.key.keysym.sym

struct {
	SDL_Window * win;
	SDL_Surface * sur;
	SDL_Renderer * ren;
} _askfile_winrs;


char * text;
// int _askfile_start = 0;
TTF_Font * font;
SDL_Color _askfile_color = {255, 255, 255};
SDL_TimerID _update_id;

int _askfile_shift = 0;

void _askfile_show_error(const char * title, const char * content) {
	const char * error = SDL_GetError();
	char * full = (char *)malloc(sizeof(char) * (strlen(content) + strlen(error) + 4));
	strcpy(full, content);
	strcat(full, " : ");
	strcat(full, error);
	if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, title, full, NULL) != 0) {
		fprintf(stderr, full);
		fprintf(stderr, "\n");
	}
}

Uint32 _update_text(Uint32 interval, void * param) {
	SDL_RenderClear(_askfile_winrs.ren);

	SDL_Texture * text = SDL_CreateTextureFromSurface(_askfile_winrs.ren, _askfile_winrs.sur);
	SDL_RenderCopy(_askfile_winrs.ren, text, NULL, NULL);
	SDL_RenderPresent(_askfile_winrs.ren);
	return interval;
}

void _askfile_update_text() {
	SDL_Rect rect = {20, 14, 179, 24};

	SDL_FillRect(_askfile_winrs.sur, &rect, 0);

	SDL_Surface * sur;
	sur = TTF_RenderText_Blended(font, text, _askfile_color);
	SDL_BlitSurface(sur, NULL, _askfile_winrs.sur, &rect);
	SDL_FreeSurface(sur);
}

void _askfile_init() {
	font = TTF_OpenFont("fonts/font.ttf", 18);
	if (!font) {
		_askfile_show_error("Font Error", "Could not load Font!");
		exit(1);
	}
	_askfile_winrs.win = SDL_CreateWindow("Open File",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			300, 50,
			SDL_WINDOW_SHOWN);
	if (!_askfile_winrs.win) {
		_askfile_show_error("Init Error", "Could Not create window");
		exit(1);
	}

	_askfile_winrs.ren = SDL_CreateRenderer(_askfile_winrs.win, -1, SDL_RENDERER_PRESENTVSYNC);
	if (!_askfile_winrs.ren) {
		_askfile_show_error("Init Error", "Could Not Create renderer");
		exit(1);
	}

	_askfile_winrs.sur = SDL_GetWindowSurface(_askfile_winrs.win);
	if (!_askfile_winrs.sur) {
		_askfile_show_error("Init Error", "Could Not get window surface");
		exit(1);
	}

	_update_id = SDL_AddTimer(100, _update_text, NULL);
}

void _askfile_quit() {
	SDL_RemoveTimer(_update_id);
	SDL_DestroyRenderer(_askfile_winrs.ren);
	SDL_DestroyWindow(_askfile_winrs.win);
	// printf("Quit askfile\n");
}

char * _askfile_delete_text(char * text) {
	text[strlen(text) - 1] = '\0';
	// printf("%s\n", text);
	return text;
}

char * _askfile_addk(char * text, char k) {
	if (_askfile_shift == 1 && k >= 97 && 122 >= k) {
		k = toupper(k);
	}
	if (_askfile_shift == 1) {
		switch(k) {
			case '-': k = '_'; break;
			case '=': k = '+'; break;
			case '\'': k = '"'; break;
			case ';': k = ':'; break;
			case '/': k = '?'; break;
			case '.': k = '>'; break;
			case ',': k = '<'; break;
			case '[': k = '{'; break;
			case ']': k = '}'; break;
			case '\\': k = '|'; break;
		}
		if (48 <= k && 57 >= k) {
			char l[11] = ")!@#$%^&*(";
			k = l[k - 48];
		}
	}
	if (k >= 32 && 126 >= k) {
		int l = strlen(text);
		text = (char *)realloc(text, sizeof(char) * (l + 2));
		text[l] = k;
		text[l + 1] = '\0';
	}
	// printf("%s\n", text);
	return text;
}

int _askfile_checkClick(SDL_Rect rect, SDL_Event e) {
	int x = e.button.x;
	int y = e.button.y;
	if ((x >= rect.x && rect.x + rect.w >= x) && (y >= rect.y && rect.y + rect.h >= y)) {
		return 1;
	}
	return 0;
}

char * askfile() {
	_askfile_init();
	// printf("_askfile_init\n");
	SDL_Rect rect = {19, 12, 182, 27}; // 18pt 24px
	SDL_Rect recti = {20, 13, 180, 25};
	SDL_FillRect(_askfile_winrs.sur, &rect, SDL_MapRGB(_askfile_winrs.sur->format, 255, 255, 255));
	SDL_FillRect(_askfile_winrs.sur, &recti, 0);

	// printf("Fill Rect1\n");

	SDL_Rect rects = {219, 12, 62, 27}; // 18pt 24px
	SDL_Rect rectsi = {220, 13, 60, 25};
	SDL_FillRect(_askfile_winrs.sur, &rects, SDL_MapRGB(_askfile_winrs.sur->format, 255, 255, 255));
	SDL_FillRect(_askfile_winrs.sur, &rectsi, 0);
	// printf("Fill Rect2\n");

	SDL_Rect rectst = {225, 14, 0, 0};
	SDL_Surface * ___sur = TTF_RenderText_Blended(font, "select", _askfile_color);
	SDL_BlitSurface(___sur, NULL, _askfile_winrs.sur, &rectst);
	SDL_FreeSurface(___sur);
	int b_down = 0;
	// printf("Fill Text\n");

	SDL_Event e;
	SDL_UpdateWindowSurface(_askfile_winrs.win);

	text = (char *)malloc(sizeof(char));
	text[0] = '\0';

	while (1) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_KEYDOWN:
					if (key == SDLK_RSHIFT || key == SDLK_LSHIFT) {
						_askfile_shift = 1;
					}
					break;
				case SDL_KEYUP:
					if (key == SDLK_RSHIFT || key == SDLK_LSHIFT) {
						_askfile_shift = 0;
					} else if (key == SDLK_DELETE || key == SDLK_BACKSPACE) {
						text = _askfile_delete_text(text);
					} else if (key == SDLK_RETURN || key == SDLK_RETURN2) {
						// printf("return pressed!\n");
						goto __mouse;
					} else {
						text = _askfile_addk(text, key);
					} _askfile_update_text();
					break;
				case SDL_MOUSEBUTTONUP:
					if (_askfile_checkClick(rectsi, e) && b_down == 1) {
__mouse:
						if (access(text, 4)) {
							_askfile_show_error("path error", "Not validate path");
							text[0] = '\0';
							_askfile_update_text();
							break;
						}
						_askfile_quit();
						return text;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (_askfile_checkClick(rectsi, e)) {
						b_down = 1;
					}
					break;
				case SDL_QUIT:
					// printf("Askfile quit!\n");
					_askfile_quit();
					return NULL;
				case SDL_WINDOWEVENT:
					switch (e.window.event) {
						case SDL_WINDOWEVENT_CLOSE:
							_askfile_quit();
							return NULL;
					}
					break;
				default:
					break;
			}
		}
	}
	return NULL;
}

int _askfile_main() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		_askfile_show_error("Init Error", "Could Not _askfile_init sdl");
		exit(1);
	}
	atexit(SDL_Quit);

	if (TTF_Init() < 0) {
		_askfile_show_error("Init Error", "Could Not Init ttf");
		exit(1);
	}

	// _askfile_show_error("test", "Test !!!!");
	// exit(1);

	char * fn = askfile();
	// printf("finally get filename:%s|end\n", fn);

	return 0;
}
