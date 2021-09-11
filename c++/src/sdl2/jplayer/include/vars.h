#ifndef VARS_H
#define VARS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// const the info of the window
const int width = 300;
const int height = 200;
const char * title = "Jplayer";

// The main struct of the win
// typedef is not forced, but clearer error when debuging
struct __WINRS {
	SDL_Window * win;
	SDL_Surface * sur;
	SDL_Renderer * ren;
} winrs;
typedef struct __WINRS _WINRS;
void init_winrs();

// the struct of the stop and start image
struct __IMGS {
	SDL_Surface * stop;
	SDL_Surface * start;
	int down;
} imgs;
typedef struct __IMGS _IMGS;
const char * imgs_stop_fn = "image/stop.bmp";
const char * imgs_start_fn = "image/play.bmp";
SDL_Rect imgs_place = {25, 40, 30, 30};
void init_imgs();
void fill_imgs();

// scroller scl
struct __SCROLLER {
	SDL_Rect front;
	SDL_Rect left;
	SDL_Rect back;
	double x_perc;
	int down;
} scl;
typedef struct __SCROLLER _SCROLLER;
SDL_Rect scl_place = {17, 20, 265, 15};
void init_scl();
void quit_scl();
void change_scl(int x);
void fill_scl();
void update_scl();
Uint32 _update_scl(Uint32 interval, void * param);
SDL_TimerID _update_scl_id;

// times showing
// Also fonts struct
struct __FONTS {
	TTF_Font * f18; // 18pt, 24px
	TTF_Font * f15; // 15pt, 20px
	TTF_Font * f12; // 12pt, 16px
} fonts;
SDL_Color color = {255, 255, 255}; // white
void init_fonts();
void quit_fonts();
SDL_Surface * renderText(TTF_Font * , const char *);

void init_times();
void quit_times();
SDL_Rect times_place = {60, 50, 0, 0};
char * _old_times = NULL;
Uint32 _update_times(Uint32 interval, void * param);
SDL_TimerID _update_times_id;

// for showing music file name on the 
SDL_Rect fn_place = {100, 78, 0, 24}; // 18pt
int set_filename(const char *);

struct {
	SDL_Surface * sur;
	SDL_Rect border; // {24, 79, 102, 18};
	SDL_Rect inside; // {25, 80, 100, 16};
	int down;
} slt;
void init_slt();
void quit_slt();



// a short function to fill the surface
// if the rect_pointer is NULL, fill the whole surface by the color
// color should be the result of SDL_MapRGB(winrs.sur->format, ?r, ?g, ?b);
int fillRect(SDL_Rect * rect, Uint32 color);

// The function to check if there's something wrong with the function
// if result is not 0, print the s to stderr, and SDL_GetError call to it
// That means s must end with "%s\n", or there would be something wrong
int check(int result, const char * s);

// use SDL_Timer subsystem to update the win,
// interval usually set to 1000 / 24, that means 24fps
Uint32 _update_ren(Uint32 interval, void * param);
SDL_TimerID _update_ren_id;

#endif // VARS_H
