#include "../jsnd/jsnd.h"

int main() {
	MP3_FILE * mfp = NULL;
	MP3_FILE * mfp2 = NULL;
	WAV_FILE * wfp = NULL;

	mfp = mp3_load("sound/1.mp3");
	mfp2 = mp3_load("sound/3.mp3");
	wfp = wav_load("sound/1.wav");

	printf("MP3 test\n");
	mp3_printinfo(mfp);

	printf("\nMP3 test 2\n");
	mp3_printinfo(mfp2);

	printf("\nWAV test\n");
	wav_printinfo(wfp);

	mp3_free(mfp);
	wav_free(wfp);

	if (music_type("sound/1.mp3") != 0 || music_type("sound/1.wav") != 1) {
		printf("Could not succeed in checking music type!\n");
		return 1;
	}
	return 0;
}
