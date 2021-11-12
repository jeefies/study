#include <stdlib.h>
#include <linux/fb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <SDL2/SDL.h>

struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;

SDL_Window * win = NULL;
SDL_Renderer * ren = NULL;
SDL_Surface * sur = NULL;

int c16to32(int c16) {
	Uint32 c32 =0;

	c32 |= (c16 & 0x1f) << 3;
	c32 |= ((c16 >> 5) & 0x3f) << (8 + 2);
	c32 |= ((c16 >> 11) & 0x3f) << (16 + 3);

	return c32;
}

void copy_data(char * fbp, Uint32 * pixels, long pix) {
	Uint32 buf;
	for (int i = 0; i < pix; i++) {
		buf = (fbp[i * 2] << 8) | fbp[i * 2 + 1];
		pixels[i] = c16to32(buf);
	}
}


int main() {
	// Init fb file
	int fp = 0;
	char * fpb;
	fp = open("/dev/fb0", O_RDWR);

	if (fp < 0) {
		printf("Could not open fb file\n");
		return 1;
	}

	if (ioctl(fp, FBIOGET_FSCREENINFO,  &finfo)) {
		printf("Could not read fixed screen info\n");
		return 1;
	}

	if (ioctl(fp, FBIOGET_VSCREENINFO, &vinfo)) {
		printf("Could not read varieable\n");
		return 1;
	}

	long screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
	long pixnum = vinfo.xres * vinfo.yres;
	printf("bits: %d\n", vinfo.bits_per_pixel);
	fpb = (char *)mmap(0, screensize,  PROT_READ | PROT_WRITE, MAP_SHARED, fp,  0);

	if ((long)fpb == -1) {
		printf("Could not map bufferframe device to memory\n");
		return 1;
	}

	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_CreateWindow("FB Screen",  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			vinfo.xres, vinfo.yres, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
	sur = SDL_GetWindowSurface(win);

	Uint32 * pixels = sur->pixels;
	printf("sdl bits: %d\n", sur->format->BitsPerPixel);

	SDL_Event e;
	SDL_Texture  * text = NULL;
	while (1) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym) {
						case SDLK_ESCAPE:
							goto __done;
					}
				case SDL_QUIT:
					goto __done;
			}
		}

		copy_data(fpb, pixels, pixnum);
		printf("Copied!\n");
		text = SDL_CreateTextureFromSurface(ren, sur);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, text, NULL, NULL);
		SDL_RenderPresent(ren);
	}
__done:
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}
