#include <stdlib.h>
#include <stdio.h>

int music_type(const char*);

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

struct _FRAME_HEADER {
	// all bits
	// unsigned short sync; // 11
	unsigned char version; // 2
	unsigned char layer; // 2
	unsigned char ifCRC; // 1
	unsigned short bitrate; // 4
	unsigned short freq; // 2

	unsigned char channels;
	unsigned char extension;
	unsigned char copyright;
	unsigned char origin;
	unsigned char emphasis;
};
typedef struct _FRAME_HEADER FRAME_HEADER;

struct _MP3_INFO {
	char version[2];
	int tag_size;
	int data_size;
	FRAME_HEADER fh;
	long time; // ms
};
typedef struct _MP3_INFO MP3_INFO;

struct _MP3_FILE {
	FILE *fp;
	long seek;
	MP3_INFO *info;
};
typedef struct _MP3_FILE MP3_FILE;

short _read1(MP3_FILE*);
int _readn(MP3_FILE*, int, int);
long mp3_seek(MP3_FILE*, long);
long mp3_seek2(MP3_FILE*, long);
long mp3_seek3(MP3_FILE*, long);

MP3_FILE * mp3_load(const char*);
MP3_INFO * mp3_getinfo(MP3_FILE*);
int mp3_data_start(MP3_FILE*);
char *mp3_mpegversion(MP3_FILE*);
char *mp3_layerversion(MP3_FILE*);
char *mp3_mpegversioni(MP3_INFO*);
char *mp3_layerversioni(MP3_INFO*);
void mp3_printinfo(MP3_FILE*);
void mp3_free(MP3_FILE*);
