#include <stdio.h>
#include <stdlib.h>


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

const int freq = 44100;
const int channels = 2;
const int samplesize = 2048;
Mix_Music *music = NULL;
const char * HelpMessage = "type h for help message\ntype l to load a media file\ntype s to start the media\n"
"type p to pause the media\ntype q to quit\ntype t to set the time to play\n"
"type r to restart the music\n";

#ifdef __cpluplus
extern "C" {
#endif

int init();
int quit();
int loadmedia(const char* filename);
int play();
int ask();
char * input();
int settime(double sec);

#ifdef __cpluplus
}
#endif

int ask() {
	printf(">>> ");
	char mod;
	scanf("%c", &mod);
	char fn[20];
	double sec;

	switch (mod) {
		case 'h':
			printf("Help Message:\n");
			printf(HelpMessage);
			break;
		case 'l':
			getchar();
			printf("filename: ");
			scanf("%s", fn);
			loadmedia(fn);
			break;
		case 's':
			play();
			break;
		case 'p':
			Mix_PauseMusic();
			printf("Paused!\n");
			break;
		case 'q':
			printf("Good Bye!\n");
			return 1;
		case '\0':
			printf("Quit!\n");
			return 1;
			break;
		case 't':
			getchar();
			printf("Set Time to (s):");
			scanf("%lf", &sec);
			settime(sec);
			break;
		case 'r':
			Mix_RewindMusic();
			break;
		default:
			break;
	}
	if (getchar() == -1) return 1;
	return 0;
}

int init() {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("Could not Init SDL: %s\n", SDL_GetError());
		return 1;
	}

	if (Mix_OpenAudio(freq, MIX_DEFAULT_FORMAT, channels, samplesize) < 0) {
		printf("Could not OpenAudio!: %s\n", Mix_GetError());
		return 1;
	}
	return 0;
}

int loadmedia(const char* filename) {
	if (music != NULL) {
		Mix_FreeMusic(music);
	}
	music = Mix_LoadMUS(filename);
	if (music == NULL) {
		printf("Could Not load sound file %s: %s\n", filename, Mix_GetError());
		return 1;
	}
	return 0;
}


int quit() {
	Mix_FreeMusic(music);
	Mix_Quit();
	SDL_Quit();
}

int play() {
	printf("Start playing\n");
	if (Mix_PlayingMusic() == 0) { // It's to check if the music is playing
		Mix_PlayMusic(music, 0);
		// The sencond refers to the times to repeat
		// if it's -1 , repeat it again and again
	} else if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
		// if the music is paused, start the music at the old place
	}
	return 0;
}

int settime(double sec) {
	if (music == NULL) {
		printf("No Music loaded, type l to load the music first!\n");
		return 1;
	}
	Mix_RewindMusic();
	int r;
	if ((r = Mix_SetMusicPosition(sec)) != 0) 
		printf("Failed to set music position or timed to much: %s\n", Mix_GetError());
	return r;
}

int main(int argc, char * argv[]) {
	init();
	if (argc >= 2 && strcmp(argv[1], "play") == 0) {
		while (1) {
			for (int i = 2; i < argc; i++) {
				loadmedia(argv[i]);
				play();
				while (Mix_PlayingMusic()) SDL_Delay(100);
			}
		}
	}
	while (1 == 1) {
		if (ask() == 1) break;
	}
	quit();
}
