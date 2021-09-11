#include "Jwave.h"

int main() {
	char * fn = "../sounds/1.wav";
	WAV_FILE * wf = wav_load(fn);
	wav_printinfo(wf);
	wav_free(wf);
	return 0;
}
