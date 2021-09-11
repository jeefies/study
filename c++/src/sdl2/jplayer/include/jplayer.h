#ifndef JPLAYER_H
#define JPLAYER_H
#include <SDL2/SDL.h>

#define DEBUG

#define SDL_INIT SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_EVENTS
const int samplesize = 1 << 13;

void mainloop();

#endif // JPLAYER_H
