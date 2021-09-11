#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "jsnd.h"

#define CHARL sizeof(char)

long _file_size(FILE*);

unsigned short _freqnum_tofreq(FRAME_HEADER, short);
unsigned short _bitcase_to_rate(FRAME_HEADER, char);

// GLOABL USAGES

int music_type(const char * fn) {
	FILE * fp = NULL;
	if ((fp = fopen(fn, "rb")) == NULL) {
		perror("could not open file");
		exit(1);
	}

	char f4[4];
	int r;
	fread(f4, 1, 4, fp);
	if (f4[0] == 'I' && f4[1] == 'D' && f4[2] == '3') // MP3 music
		r = 0;
	else if (f4[0] == 'R' && f4[1] == 'I' && f4[2] == 'F' && f4[3] == 'F') // WAV
		r = 1;
	else r = -1; // Undefine
	fclose(fp);

	return r;
}


// MP3 MUSIC ANALYZER START

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
	return mfp->seek;
}
long mp3_seek2(MP3_FILE *mfp, long seek) {
	fseek(mfp->fp, seek, SEEK_CUR);
	mfp->seek += seek;
	return mfp->seek;
}
long mp3_seek3(MP3_FILE *mfp, long seek) {
	fseek(mfp->fp, seek, SEEK_END);
	mfp->seek = ftell(mfp->fp);
	return mfp->seek;
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
	if ((num >> 5 & 0x7ff) != 0x7ff) {
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

	info->time = s * 8 / bitrate; // ms
	free(abc);

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
			"extension: %d\ncopyright: %d\norigin: %d\nemphasis: %d\nfreq: %d\nbitrate: %d\n"
			"music time(ms): %ld\n", 
			info->version[0], info->version[1], info->tag_size, mp3_mpegversioni(info), mp3_layerversioni(info), 
			fh.ifCRC, fh.channels, fh.extension, fh.copyright, fh.origin, fh.emphasis, fh.freq, fh.bitrate, info->time);
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


// WAV MUSIC ANALYZER START

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
	into[size] = '\0';
	wav_seek(wfp, wfp->seek);
}

// Print The wavefile's info to the screen
void wav_printinfo(WAV_FILE * wfp) {
	WAV_INFO info = *(wfp->info);
	printf("format: %d\nchannels: %d\nsample_per_sec: %d\nbytes_per_sec: %d\nmusic time(ms): %ld\ndata size: %ld\n",
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
	// notice wav_read will not seek the file
	wav_read(wfp, fact, 4);

	// it's turn to fact chunk
	if (strcmp(fact, "fact") == 0) {
		data_s = _readf4(wfp);
		wav_seek(wfp, wfp->seek + data_s);
		goto __check;
	// No facts chunk, but data chunk starts
	} else if (strcmp(fact, "data") == 0) {
		printf("data chunk %ld\n", wfp->seek);
		return (short)wfp->seek + 4;
	// Have No pre-chunk here!
	} else {
		int s;
		while (1) {
			s = wfp->seek;
			wav_read(wfp, fact, 4);
			// printf("read chunk %s at %ld \n", fact, wfp->seek);
			if (strcmp(fact, "data") == 0) {
				break;
			}
			wav_seek(wfp, s + 1);
		}
		return wfp->seek + 4;
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

unsigned short _bitcase_to_rate(FRAME_HEADER fh, char bitcase) {
	if (fh.version == 3) { // MPEG 1
		switch (fh.layer) {
			case 1: // Layer 3
				switch (bitcase) {
					case 0: // 0000
						return 0;
					case 1: // 0001
						return 32;
					case 2: // 0010
						return 40;
					case 3: // 0011
						return 48;
					case 4: // 0100
						return 56;
					case 5: // 0101
						return 64;
					case 6: // 0110
						return 80;
					case 7: // 0111
						return 96;
					case 8: // 1000
						return 112;
					case 9: // 1001
						return 128;
					case 10: // 1010
						return 160;
					case 11: // 1011
						return 192;
					case 12: // 1100
						return 224;
					case 13: // 1101
						return 256;
					case 14: // 1110
						return 320;
					case 15: // 1111
						return 0;
					default:
						printf("Not validate num\n");
						return 0;
				};
			case 2: // Layer 2
				switch (bitcase) {
					case 0: // 0000
						return 0;
					case 1: // 0001
						return 32;
					case 2: // 0010
						return 48;
					case 3: // 0011
						return 56;
					case 4: // 0100
						return 64;
					case 5: // 0101
						return 80;
					case 6: // 0110
						return 96;
					case 7: // 0111
						return 112;
					case 8: // 1000
						return 128;
					case 9: // 1001
						return 160;
					case 10: // 1010
						return  192;
					case 11: // 1011
						return 224;
					case 12: // 1100
						return 256;
					case 13: // 1101
						return 320;
					case 14: // 1110
						return 384;
					case 15: // 1111
						return 0;
					default:
						printf("Not validate num\n");
						return 0;
				}
			case 3: // Layer 1
				switch (bitcase) {
					case 0: // 0000
						return 0;
					case 1: // 0001
						return 32;
					case 2: // 0010
						return 64;
					case 3: // 0011
						return 96;
					case 4: // 0100
						return 128;
					case 5: // 0101
						return 160;
					case 6: // 0110
						return 192;
					case 7: // 0111
						return 224;
					case 8: // 1000
						return 256;
					case 9: // 1001
						return 288;
					case 10: // 1010
						return 320;
					case 11: // 1011
						return 352;
					case 12: // 1100
						return 384;
					case 13: // 1101
						return 416;
					case 14: // 1110
						return 448;
					case 15: // 1111
						return 0;
					default:
						printf("Not validate num\n");
						return 0;
				}
			default:
				return 0;
		}
	} else if (fh.version == 1) { // UNDEFINE
		printf("Undefine version, could not get bitrate\n");
		return 0;
	} else { // MPEG 2 or MPEG 2.5
		switch (fh.layer) {
			case 1: // Layer 3
				switch (bitcase) {
					case 0: // 0000
						return 0;
					case 1: // 0001
						return 8;
					case 2: // 0010
						return 16;
					case 3: // 0011
						return 24;
					case 4: // 0100
						return 32;
					case 5: // 0101
						return 64;
					case 6: // 0110
						return 80;
					case 7: // 0111
						return 56;
					case 8: // 1000
						return 64;
					case 9: // 1001
						return 80;
					case 10: // 1010
						return 96;
					case 11: // 1011
						return 112;
					case 12: // 1100
						return 128;
					case 13: // 1101
						return 256;
					case 14: // 1110
						return 320;
					case 15: // 1111
						return 0;
					default:
						printf("Not validate num\n");
						return 0;
                }
			case 2: // Layer 2
				switch (bitcase) {
					case 0: // 0000
						return 0;
					case 1: // 0001
						return 32;
					case 2: // 0010
						return 48;
					case 3: // 0011
						return 56;
					case 4: // 0100
						return 64;
					case 5: // 0101
						return 80;
					case 6: // 0110
						return 96;
					case 7: // 0111
						return 112;
					case 8: // 1000
						return 128;
					case 9: // 1001
						return 160;
					case 10: // 1010
						return 192;
					case 11: // 1011
						return 224;
					case 12: // 1100
						return 256;
					case 13: // 1101
						return 320;
					case 14: // 1110
						return 160;
					case 15: // 1111
						return 0;
					default:
						printf("Not validate num\n");
						return 0;
				}
			case 3: // Layer 1
				switch (bitcase) {
					case 0: // 0000
						return 0;
					case 1: // 0001
						return 32;
					case 2: // 0010
						return 64;
					case 3: // 0011
						return 96;
					case 4: // 0100
						return 128;
					case 5: // 0101
						return 160;
					case 6: // 0110
						return 192;
					case 7: // 0111
						return 224;
					case 8: // 1000
						return 256;
					case 9: // 1001
						return 288;
					case 10: // 1010
						return 320;
					case 11: // 1011
						return 352;
					case 12: // 1100
						return 384;
					case 13: // 1101
						return 416;
					case 14: // 1110
						return 448;
					case 15: // 1111
						return 0;
					default:
						printf("Not validate num\n");
						return 0;
				}
			default:
				return 0;
		}
	}
}
unsigned short _freqnum_tofreq(FRAME_HEADER fh, short freqn) {
    switch (fh.version) {
        case 0: // MPEG2.5
            switch(freqn) {
                case 0: return 11025;
                case 1: return 12000;
                case 2: return 8000;
                default: return 0;
            }; break;
        case 2: // MPEG2
            switch(freqn) {
                case 0: return 22050;
                case 1: return 24000;
                case 2: return 16000;
                default: return 0;
            }; break;
        case 3: // MPEG1
            switch (freqn) {
                case 0: return 44100;
                case 1: return 48000;
                case 2: return 32000;
                default: return 0;
            }
        default:
            printf("Not validate Mpeg format!\n");
            return 0;
     }
}
