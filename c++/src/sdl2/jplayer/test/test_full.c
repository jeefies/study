#include "snd.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

struct __MUSIC;
extern struct __MUSIC mus;

int main() {
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1 << 13);
	atexit(Mix_Quit);

	load_media("sound/1.mp3");


	start();

	/*
	for (int i = 0; i < 3; i++) {
		SDL_Delay(5 * 1000);
		printf("%d\n", i * 5 + 5);
	}
	*/

	set_ntime(15 * 1000);
	// BUG, true set to 7s end, nearly 8s

	SDL_Delay(10 * 1000);
	printf("Next\n");

	set_ntime(25 * 1000);
	// BUG, true set to 12s, about earlier
	SDL_Delay(10 * 1000);

	// maybe it should add twice, test again
	// after testing, it's nearly right now
	// maybe i should report this bug

	stop();

	Mix_FreeMusic(mus.mus);
}
