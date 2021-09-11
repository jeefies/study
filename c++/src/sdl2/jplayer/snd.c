#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <jsnd.h>

#include "snd.h"

/* third section
 * for define music functions,
 * now they haven't declare here
 */
extern int check(int, const char *);
extern int set_filename(const char *);

void no_mus_e() {
	if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "No Music", "There's no music loaded!", NULL) != 0) {
		fprintf(stderr, "There's no music loaded!\n");
	}
}

void show_e(const char * s) {
	if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Music Error", s, NULL) != 0) {
		fprintf(stderr, "Could not show message |%s|: %s\n", s, SDL_GetError());
	}
}

void load_media(const char* fn) {
	int mt = music_type(fn);
	if (mt == 0) { // Mp3 file
		MP3_FILE * mfp = mp3_load(fn);
		mus.mtime = mfp->info->time;
		// mp3_printinfo(mfp);
		mp3_free(mfp);
	} else if (mt == 1) { // Wav file
		WAV_FILE * wfp = wav_load(fn);
		mus.mtime = wfp->info->time;
		// wav_printinfo(wfp);
		wav_free(wfp);
	} else {
		show_e("Could not get music type");
		return;
	}

	if (mus.mus) {
		Mix_FreeMusic(mus.mus);
	}
	mus.mus = NULL;
	mus.stopped = 1;

	mus.mus = Mix_LoadMUS(fn);
	if (mus.mus == NULL) {
		const char * e = SDL_GetError();
		const char * e2 = "Could not load music: %s\n";
		char * emsg = (char *)malloc(sizeof(char) * (strlen(e) + strlen(e2)));
		sprintf(emsg, e2, e);
		show_e(emsg);
		return;
	}
	set_mtime();
	printf("Load media %s\n", fn);
	set_filename(fn);
}

void set_mtime() {
	int mt = mus.mtime / 1000;
	int sec = mt % 60;
	int min = (mt - sec) / 60;
	mus.mtimes[0] = min;
	mus.mtimes[1] = sec;
}


int get_time() {
	return mus.mtime;
}

int get_ntime() {
	switch (state()) {
		case -1:
			no_mus_e();
			return 0;
		case 0:
			return 0;
		case 2:
			return mus.ntime;
	}
	return mus.ntime + SDL_GetTicks() - mus.start_time;
}

char * get_times() {
	char * times = (char *)malloc(sizeof(char) * 6);
	sprintf(times, "%02d:%02d", mus.mtimes[0], mus.mtimes[1]);
	return times;
}

char * get_ntimes() {
	int mt = get_ntime() / 1000;
	int sec = mt % 60;
	int min = (mt - sec) / 60;
	char * s = (char *)malloc(sizeof(char) * 12);
	sprintf(s, "%02d:%02d/%02d:%02d", min, sec, mus.mtimes[0], mus.mtimes[1]);
	return s;
}

int set_ntime(int ms) {
	if (state() == -1) {
		no_mus_e();
	}
	double sec = 1000;
	sec = ms / sec;
	int _n_stop = 0;
	if (state() == 0 || state() == 2) _n_stop = 1;
	start();
	Mix_RewindMusic();
	// printf("set to time %lfs(%dms), need stop=%d\n", sec, ms, _n_stop);
	if (Mix_SetMusicPosition(sec) != 0) {
		/*
		const char * e = SDL_GetError();
		const char * e2 = "Could not set music time: %s";
		char * emsg = (char *)malloc(sizeof(char) * (strlen(e) + strlen(e2)));
		sprintf(emsg, e2, e);
		*/
		char * emsg = "Do not support set time for this music type";
		show_e(emsg);
		if (_n_stop) stop();
		return 1;
	}
	// printf("continue\n");
	if (_n_stop) stop();
	mus.start_time = SDL_GetTicks();
	mus.ntime = ms;
	return 0;
}

int state() {
	if (!mus.mus) {
		return -1;
	}
	if (Mix_PlayingMusic() == 0) // is not playing
		return 0;
	else if (Mix_PlayingMusic() == 1) // is playing or stopped
		if (mus.stopped) return 2; // stopped
	return 1;
}

int start() {
	switch (state()) {
		case -1:
			no_mus_e();
			return 1;
		case 0: // nothing played
			Mix_PlayMusic(mus.mus, 0);
			mus.start_time = SDL_GetTicks();
			mus.stopped = 0;
			break;
		case 1: // is playing
			break;
		case 2: // stopped
			Mix_ResumeMusic();
			mus.start_time = SDL_GetTicks();
			mus.stopped = 0;
			break;
	}
	return 0;
}

int stop() {
	if (state() == -1) {
		no_mus_e();
		return 1;
	}
	if (state()) {
		Mix_PauseMusic();
		mus.ntime += SDL_GetTicks() - mus.start_time;
		// printf("stopped\n");
	}
	mus.stopped = 1;
	return 0;
}

int restart() {
	switch (state()) {
		case -1:
			no_mus_e(); return 1;
		case 0:
			Mix_ResumeMusic();
			break;
		case 1:
		case 2:
			set_ntime(0);
			start();
	}
	return 0;
}
