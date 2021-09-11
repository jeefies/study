#include <SDL2/SDL_mixer.h>

// the struct of the musics
struct __MUSIC {
	Mix_Music * mus;
	int mtime; // for music time(ms)
	int mtimes[2]; // for music time(min, sec)
	char * fn; // for filename, basename
	int ntime;
	int stopped;
	int start_time;
} mus;
typedef struct __MUSIC _MUSIC;

void load_media(const char*);

int get_time();
int get_ntime();
char * get_times();
char * get_ntimes();
void set_mtime();

int set_ntime(int ms);

int state();
int start();
int stop();
int restart();

void no_mus_e();
