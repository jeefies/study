#include <SDL2/SDL.h>
#include <com_jsdl_jsdl.h>

SDL_Window * win;

JNIEXPORT void JNICALL Java_com_jsdl_jsdl_Init(JNIEnv * env, jobject obj, jint flags) {
	Uint32 flag = (Uint32)flags;

	SDL_Init(flag);
}

JNIEXPORT void JNICALL Java_com_jsdl_jsdl_CreateWindow(JNIEnv * env, jobject obj, jstring str, jint w, jint h) {
	// Convert jstring into cstring
	const char * title = (*env)->GetStringUTFChars(env, str, NULL);

	win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)w, (int)h, SDL_WINDOW_SHOWN);
}

JNIEXPORT void JNICALL Java_com_jsdl_jsdl_Delay(JNIEnv * env, jobject obj, jint ms) {
	int ms_ = (int)ms;

	SDL_Delay(ms);
}

JNIEXPORT void JNICALL Java_com_jsdl_jsdl_Quit(JNIEnv * env, jobject obj) {
	SDL_Quit();
}
