#ifndef JMP3_C
#define JMP3_C

#include <string.h>
#include "Jmp3.h"

#define CHARL sizeof(char)

long _file_size(FILE*);

unsigned short _freqnum_tofreq(FRAME_HEADER, short);
unsigned short _bitcase_to_rate(FRAME_HEADER, char);

short _read1(MP3_FILE *mfp) {
	char a[0];
	long sk = mfp->seek;
	fread(a, 1, 1, mfp->fp);
	// printf("a: %d\n", a);
	mp3_seek(mfp, sk);
	short r = 0;
	r |= a[0];
	return r;
}

long _file_size(FILE *fp) {
	long sk = ftell(fp);
	fseek(fp, 0, SEEK_END);
	long r = ftell(fp);
	fseek(fp, sk, SEEK_SET);
	return r;
}

int _readn(MP3_FILE *mfp, int n, int offset) {
	char a[n];
	long sk = mfp->seek;
	fread(a, n, 1, mfp->fp);
	/*
	printf("Read N:")
	for (int i = 0; i < n; i++) {
		printf("%d ", n);
	}
	printf("\n");
	 */
	mp3_seek(mfp, sk);
	int r = 0;
	for (int j = 0; j < n; j++) {
		r |= a[n - j - 1] << 8 * j;
	}
	return r;
}

long mp3_seek(MP3_FILE *mfp, long seek) {
	fseek(mfp->fp, seek, SEEK_SET);
	mfp->seek = seek;
}
long mp3_seek2(MP3_FILE *mfp, long seek) {
	fseek(mfp->fp, seek, SEEK_CUR);
	mfp->seek += seek;
}
long mp3_seek3(MP3_FILE *mfp, long seek) {
	fseek(mfp->fp, seek, SEEK_END);
	mfp->seek = ftell(mfp->fp);
}

int mp3_data_start(MP3_FILE *mfp) {
	MP3_INFO * info = mp3_getinfo(mfp);
	mp3_seek(mfp, info->tag_size + 10);
	int hd = _readn(mfp, 3, 8);
	int sk = info->tag_size + 14;
	int i;
	while (1) {
		mp3_seek(mfp, sk);
		i = _readn(mfp, 3, 8);
		// printf("Read %x at %d\n", i, sk);
		if (hd == i) {
			return sk + 4;
		}
		sk++;
	}
}

MP3_INFO *mp3_getinfo(MP3_FILE *mfp) {
	if (mfp->info != NULL)
		return mfp->info;
	MP3_INFO *info = (MP3_INFO *)malloc(sizeof(MP3_INFO));
	mp3_seek(mfp, 0);

	// check for the filetype
	char *abc = (char *)calloc(sizeof(char), 4);
	fread(abc, 3, 1, mfp->fp);
	abc[4] = '\0';
	if (strcmp(abc, "ID3")) {
		printf("Not validate mp3 file!");
		return NULL;
	}
	free(abc);

	// Read the version and the revision
	info->version[0] = _read1(mfp);
	mp3_seek(mfp, 4);
	info->version[1] = _read1(mfp);

	// The tag size
	mp3_seek(mfp, 6);
	int size = _readn(mfp, 4, 7);
	info->tag_size = size;
	// printf("tag size: %d\n", size);

	// the tag infos pass
	mp3_seek(mfp, 10 + size);

	// 数据帧帧头
	short num = _readn(mfp, 2, 8);
	FRAME_HEADER fh;

	// first two bytes
	// sync info (first 11 bits are all 1)
	if (num >> 5 & 0x7ff != 0x7ff) {
		printf("Could not read sync version!\n");
		free(info);
		return NULL;
	}
	char version, layer, ifCRC;
	fh.version = version = (num >> 3) & 3;
	fh.layer = layer = (num >> 1) & 3;
	fh.ifCRC = ifCRC = num & 1;

	// third bytes (bitrate and freq)
	// last bits has no used
	mp3_seek(mfp, 12 + size);
	num = _read1(mfp);
	// printf("3rd bytes: %x\n", num);
	short bitcase = num >> 4;
	// printf("bitcase: %d\t", bitcase);
	unsigned short bitrate = _bitcase_to_rate(fh, bitcase);
	short freqn = (num >> 2) & 3;
	// printf("freqn: %d\n", freqn);
	unsigned short freq = _freqnum_tofreq(fh, freqn);
	fh.freq = freq;
	fh.bitrate = bitrate;

	// fourth bytes(channels 2, extension 2, copyright 1, origin 1, emphasis 2)
	mp3_seek(mfp, 13 + size);
	num = _read1(mfp);
	// printf("4th bytes: %x\n", num);
	char channels = num & 0xc0 >> 6;
	char extension = num & 0x30 >> 4;
	char copyright = num & 0x08 >> 3;
	char origin = num & 0x04 >> 2;
	char emphasis = num & 3;

	fh.channels = channels; fh.extension = extension;
	fh.copyright = copyright; fh.origin = origin; fh.emphasis = emphasis;

    info->fh = fh;
    
	/*
    printf("version: %s\nlayer: %s\nifCRC: %d\nchannels: %d\nextension: %d\ncopyright: %d\norigin: %d\nemphasis: %d\n"
        "freq: %d\nbitrate: %d\n", mp3_mpegversioni(info), mp3_layerversioni(info), ifCRC, channels,
		extension, copyright, origin, emphasis, freq, bitrate);
	*/

	// Now it's time to get the main data size
	long s = _file_size(mfp->fp) - info->tag_size;
	mp3_seek3(mfp, -128);
	fread(abc, 3, 1, mfp->fp);
	if (strcmp(abc, "TAG") == 0) {
		s -= 128;
	}

	info->data_size = s;

	mfp->time = s * 8 / bitrate; // ms

	return info;
}

char * mp3_mpegversion(MP3_FILE *mfp) {
	switch (mfp->info->fh.version) {
		case 0: // MPEG 2.5
			return "MPEG 2.5";
		case 2: // MPEG 2
			return "MPEG 2";
		case 3: // MPEG 1
			return "MPEG 1";
	}
	return "UNDEFINE";
}

char *mp3_layerversion(MP3_FILE *mfp) {
	switch (mfp->info->fh.layer) {
		case 1:
			return "layer 3";
		case 2:
			return "layer 2";
		case 3:
			return "layer 3";
	}
	return "UNDEFINE";
}

char * mp3_mpegversioni(MP3_INFO *info) {
	switch (info->fh.version) {
		case 0: // MPEG 2.5
			return "MPEG 2.5";
		case 2: // MPEG 2
			return "MPEG 2";
		case 3: // MPEG 1
			return "MPEG 1";
	}
	return "UNDEFINE";
}

char *mp3_layerversioni(MP3_INFO *info) {
	switch (info->fh.layer) {
		case 1:
			return "layer 3";
		case 2:
			return "layer 2";
		case 3:
			return "layer 3";
	}
	return "UNDEFINE";
}

void mp3_printinfo(MP3_FILE *mfp) {
	MP3_INFO *info = mfp->info;
	FRAME_HEADER fh = info->fh;
    printf("tagversion: %d.%d\ntag size: %d\nmpeg version: %s\nlayer: %s\nifCRC: %d\nchannels: %d\n"
			"extension: %d\ncopyright: %d\norigin: %d\nemphasis: %d\nfreq: %d\nbitrate: %d\n", 
			info->version[0], info->version[1], info->tag_size, mp3_mpegversioni(info), mp3_layerversioni(info), 
			fh.ifCRC, fh.channels, fh.extension, fh.copyright, fh.origin, fh.emphasis, fh.freq, fh.bitrate);
}

MP3_FILE * mp3_load(const char* fn) {
	FILE * fp = NULL;

	if ((fp = fopen(fn, "rb")) == NULL) {
		perror("Could Not Open File");
		return NULL;
	}

	MP3_FILE * mfp = (MP3_FILE *)malloc(sizeof(MP3_FILE));
	mfp->fp = fp;
	mfp->seek = 0;
	mfp->info = NULL;
	mfp->info = mp3_getinfo(mfp);
	return mfp;
}

void mp3_free(MP3_FILE* mfp) {
	fclose(mfp->fp);
	free(mfp);
}

int main(int argc, char * argv[]) {
	char * fn = (char *)malloc(CHARL);
	if (argc > 1) {
		fn = (char*)realloc(fn, CHARL * strlen(argv[1]) + CHARL);
		strcpy(fn, argv[1]);
	} else {
		fn = (char *)realloc(fn, CHARL * 13);
		strcpy(fn,  "sounds/1.mp3");
	}

	MP3_FILE * mfp = mp3_load(fn);

	mp3_printinfo(mfp);
	int st = mp3_data_start(mfp);
	printf("data start at: %d\ntime: %ld\n", st, mfp->time);

	mp3_free(mfp);
	return 0;
}

#endif // JMP3_C
