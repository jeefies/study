#include "Jmp3.h"

int main() {
	char *sounds = "../sounds/1.mp3";
	MP3_FILE * mfp = mp3_load(sounds);
	printf("MP3 File time: %ld\n", mfp->time);
	return 0;
}
