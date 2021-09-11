#ifndef JWAVE_C
#define JWAVE_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_LEN sizeof(char)
#include "Jwave.h"

// equal to fseek(wfp.fp...SEEK_SET)
void wav_seek(WAV_FILE * wfp, long pos) {
	fseek(wfp->fp, pos, SEEK_SET);
	wfp->seek = pos;
}

// equal to fseek(wfp.fp...SEEK_CUR)
void wav_seek2(WAV_FILE * wfp, long pos) {
	fseek(wfp->fp, pos, SEEK_CUR);
	wfp->seek += pos;
}

// get the wave files size (except the first 8 bytes)
long wav_filesize(WAV_FILE * wfp) {
	wav_seek(wfp, 4);
	char abcd[4];
	long size = 0;
	fread(abcd, 4, 1, wfp->fp);
	// printf("abcd: %d %d %d %d\n", abcd[0], abcd[1], abcd[2], abcd[3]);
	for (int i = 0; i < 4; i++) {
		size |= abcd[i] << 8 * i;
	}

	return size;
}

// Read the chunk size (next 4)
int _readf4(WAV_FILE * wfp) {
	char abcd[4];
	int r = 0;
	long sk = wfp->seek;
	fread(abcd, 4, 1, wfp->fp);
	// printf("abcd: %d %d %d %d\n", abcd[0], abcd[1], abcd[2], abcd[3]);
	for (int i = 0; i < 4; i++) {
		r |= abcd[i] << 8 * i;
	}
	wav_seek(wfp, wfp->seek);
	return r;
}

// Read the chunk size (next 2)
short _readf2(WAV_FILE * wfp) {
	char abcd[2];
	int r = 0;
	long sk = wfp->seek;
	fread(abcd, 2, 1, wfp->fp);
	// printf("ab: %d %d\n", abcd[0], abcd[1]);
	for (int i = 0; i < 2; i++) {
		r |= abcd[i] << 8 * i;
	}
	wav_seek(wfp, wfp->seek);
	return r;
}

// only use to read a STRING out
// notice that the last char would be changed into '\0'
// it means param into will be a string after it
void wav_read(WAV_FILE * wfp, char * into, int size) {
	fread(into, size, 1, wfp->fp);
	wav_seek(wfp, wfp->seek + size);
	into[size] = '\0';
}

// Print The wavefile's info to the screen
void wav_printinfo(WAV_FILE * wfp) {
	WAV_INFO info = *(wfp->info);
	printf("format: %d\nchannels: %d\nsample_per_sec: %d\nbytes_per_sec: %dmusic time(ms): %ld\ndata size: %ld\n",
			info.format, info.channels, info.samples, info.samplesize, info.time, wfp->data_size);
}

// Get info of the wave file, return a WAV_INFO structure
WAV_INFO *wav_getinfo(WAV_FILE * wfp) {
	if (wfp->info != NULL) {
		return wfp->info;
	}
	// short format;
	// short channels;
	// int samples; 		sample per sec
	// int samplesize; 		bytes per sec
	// short block_align;	equal to channels * samplebits / 8
	// short samplebits;  	量化等级 has 16bits, 24bits, 32bits
	// total read 16 bytes
	WAV_INFO * info = (WAV_INFO *)malloc(sizeof(WAV_INFO));
	wav_seek(wfp, 20);
	info->format = _readf2(wfp);
	wav_seek2(wfp, 2);
	info->channels = _readf2(wfp);
	wav_seek2(wfp, 2);
	info->samples = _readf4(wfp);
	wav_seek2(wfp, 4);
	info->samplesize = _readf4(wfp);
	wav_seek2(wfp, 4);
	info->block_align = _readf2(wfp);
	wav_seek2(wfp, 2);
	info->samplebits = _readf2(wfp);
	long time = wfp->data_size * 1000 / info->samplesize;
	info->time = time;
	wfp->info = info;
	return info;
}

// Get the place where the wav file's sound data start
short wav_data_start(WAV_FILE * wfp) {
	wav_seek(wfp, 16);
	int data_s = _readf4(wfp);
	wav_seek(wfp, 20 + data_s);

	char fact[5];

__check:
	wav_read(wfp, fact, 4);
	// printf("read fact %s\n", fact);

	// it's turn to fact chunk
	if (strcmp(fact, "fact") == 0) {
		data_s = _readf4(wfp);
		wav_seek(wfp, wfp->seek + data_s);
		goto __check;
	// No facts chunk, but data chunk starts
	} else if (strcmp(fact, "data") == 0) {
		return (short)wfp->seek;
	// Have No pre-chunk here!
	} else {
		int s;
		while (1) {
			s = wfp->seek;
			wav_read(wfp, fact, 4);
			if (strcmp(fact, "data") == 0) {
				break;
			}
			// printf("read chunk %s at %d \n", fact, wfp->seek);
			wav_seek(wfp, s + 1);
		}
		return wfp->seek;
	}
}


// Load a WAV_FILE structure, give a filename in
WAV_FILE * wav_load(const char * fn) {
	FILE * fp = NULL;

	// Porcess Error if Wrong
	if ((fp = fopen(fn, "rb")) == NULL) {
		char em[strlen(fn) + 21];
		sprintf(em, "Could Not Open File %s", fn);
		perror(em);
		return NULL;
	}

	WAV_FILE * wfp = (WAV_FILE *)malloc(sizeof(WAV_FILE));
	wfp->fp = fp;
	wfp->seek = 0;
	wfp->data_size = 0;
	wfp->closed = 0;
	wfp->info = NULL;
	wav_seek(wfp, wav_data_start(wfp));
	wfp->data_size = _readf4(wfp);
	wav_getinfo(wfp);
	return wfp;
}

// Better to use this before wav_free
// But there's no matter because wav_free would automatically use this
void wav_close(WAV_FILE * wfp) {
	wfp->closed = 1;
	fclose(wfp->fp);
}

// Release the resource
void wav_free(WAV_FILE * wfp) {
	if (!wfp->closed)
		wav_close(wfp);
	free(wfp);
}


int main(int argc, char * argv[]) {
	// process the music filename
	char * fn = (char *)malloc(4);
	if (argc > 1) {
		fn = (char *)realloc(fn, CHAR_LEN * strlen(argv[1]) + CHAR_LEN);
		strcpy(fn, argv[1]);
	} else {
		fn = (char *)realloc(fn, CHAR_LEN * 13);
		strcpy(fn, "sounds/1.wav");
	}

	WAV_FILE * wfp = wav_load(fn);

	// get the file size
	wav_printinfo(wfp);
	long s = wav_filesize(wfp);
	short ds = wav_data_start(wfp);

	if (s == 0) return 0;
	printf("size: %ld\ndata start at: %d\ndata size: %d\n"
			"time (milliseconds):%ld\n", s, ds, wfp->data_size, wfp->info->time);

	wav_free(wfp);
	return 0;
}

#endif // JWAVE_C
