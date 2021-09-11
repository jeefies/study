#include <stdlib.h>
#include <stdio.h>

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
};
typedef struct _MP3_INFO MP3_INFO;

struct _MP3_FILE {
	FILE *fp;
	long seek;
	long time; // ms
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
void *mp3_printinfo(MP3_FILE*);
void mp3_free(MP3_FILE*);
