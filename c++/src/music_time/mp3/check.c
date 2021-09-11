#include "Jmp3.h"

unsigned short _freqnum_tofreq(FRAME_HEADER, short);
unsigned short _bitcase_to_rate(FRAME_HEADER, char);

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
