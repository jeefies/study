#ifndef JWAVE_H
#define JWAVE_H

#include <stdlib.h>
#include <stdio.h>

struct _WAV_INFO {
	short format;
	short channels;
	int samples; // sample per sec
	int samplesize; // bytes per sec
	short block_align; // equal to channels * samplebits / 8
	short samplebits; // 量化等级 has 16bits, 24bits, 32bits
	long time; // milli second
};
typedef struct _WAV_INFO WAV_INFO;

struct _WAV_FILE {
	FILE * fp;
	long seek;
	long data_size;
	short closed;
	WAV_INFO * info;
};
typedef struct _WAV_FILE WAV_FILE;

long wav_filesize(WAV_FILE*);
WAV_FILE * wav_load(const char *);
void wav_free(WAV_FILE *);
void wav_seek(WAV_FILE *, long);
void wav_seek2(WAV_FILE *, long);
void wav_printinfo(WAV_FILE*);
void wav_read(WAV_FILE *, char*, int);
void wav_close(WAV_FILE*);
short wav_data_start(WAV_FILE*);
int _readf4(WAV_FILE*);
short _readf2(WAV_FILE*);
WAV_INFO * wav_getinfo(WAV_FILE*);

#endif // JWAVE_H
