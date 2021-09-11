package sdl

import (
    "unsafe"
)

/*
#include<SDL2/SDL.h>
int isNull(void * p) {
	if (p == NULL) {
		return 1;
	}
	return 0;
}
 */
import "C"

// const for window's postion (when creating)
const (
	WINPOS_CENTERED = int(C.SDL_WINDOWPOS_CENTERED_MASK)
	WINPOS_UNDIFIE = int(C.SDL_WINDOWPOS_UNDEFINED_MASK)
)

// const for window's flags
const (
	WIN_FULLSCREEN		= uint32(C.SDL_WINDOW_FULLSCREEN)
	WIN_OPENGL		= uint32(C.SDL_WINDOW_OPENGL)
	WIN_SHOWN		= uint32(C.SDL_WINDOW_SHOWN)
	WIN_HIDDEN		= uint32(C.SDL_WINDOW_HIDDEN)
	WIN_BORDERLESS		= uint32(C.SDL_WINDOW_BORDERLESS)
	// No complete
)

// Window's Part
func CreateWindow(title string, width, height, x_pos, y_pos int) (*Window, error) {
	return CreateWindowWithFlags(title, width, height, x_pos, y_pos, WIN_SHOWN)
}

func CreateWindowWithFlags(title string, w, h, x, y int, flags uint32) (win *Window, err error) {
	win = C.SDL_CreateWindow(C.CString(title), C.int(x), C.int(y), C.int(w), C.int(h), C.Uint32(flags))
	if (C.isNull(unsafe.Pointer(win)) == 1) {
		err = NewSDLError("Could Not Create Window")
	}
	return
}

func (win * Window) Close() {
	C.SDL_DestroyWindow(win)
}

func (win * Window) GetSurface() (*Surface) {
	return C.SDL_GetWindowSurface(win)
}

func (win * Window) GetSize() (w, h int) {
	var cw, ch C.int = 0, 0
	C.SDL_GetWindowSize(win, &cw, &ch)
	w, h = int(cw), int(ch)
	return
}

func (win * Window) UpdateSurface() {
	C.SDL_UpdateWindowSurface(win)
}
