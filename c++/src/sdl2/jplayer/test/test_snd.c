#include "snd.h"
#include <SDL2/SDL_mixer.h>

struct __MUSIC;
extern struct __MUSIC mus;

int main() {
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1 << 13);

	printf("no load music: %d\n", state());
	load_media("sound/1.mp3");
	printf("%s\n", get_times());

	printf("no playing state: %d\n", state());

	start();
	printf("state: %d\n", state());

	stop();
	printf("stop state: %d\n", state());

	Mix_FreeMusic(mus.mus);
	Mix_Quit();
}
