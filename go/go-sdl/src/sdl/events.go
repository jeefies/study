package sdl

/*
#include<SDL2/SDL.h>

Uint32 getEtype(SDL_Event * e) {
	return e->type;
}

Uint32 getKey(SDL_Event * e) {
    return e->key.keysym.sym;
}
 */
import "C"

// const SDL Event
const (
	QUIT uint32 = uint32(C.SDL_QUIT)
	KEYUP uint32 = uint32(C.SDL_KEYUP)
	KEYDOWN uint32 = uint32(C.SDL_KEYDOWN)

	KLEFT uint32 = uint32(C.SDLK_LEFT)
	KRIGHT uint32 = uint32(C.SDLK_RIGHT)
	KUP uint32 = uint32(C.SDLK_UP)
	KDOWN uint32 = uint32(C.SDLK_DOWN)

	KLSHIFT uint32 = uint32(C.SDLK_LSHIFT)
	KRSHIFT uint32 = uint32(C.SDLK_RSHIFT)
	KLCTRL uint32 = uint32(C.SDLK_LCTRL)
	KRCTRL uint32 = uint32(C.SDLK_RCTRL)

	KTAB uint32 = uint32(C.SDLK_TAB)
	KESC uint32 = uint32(C.SDLK_ESCAPE)
	KBACKSPACE uint32 = uint32(C.SDLK_BACKSPACE)
	KDEL uint32 = uint32(C.SDLK_DELETE)
)

// Event
func NewEvent() (*Event) {
	return &Event{}
}

func (e *Event) Poll() bool {
	if (C.SDL_PollEvent(e) != C.int(0)) {
		return true
	}
	return false
}

func (e *Event) Type() (uint32) {
	return uint32(C.getEtype(e))
}

func (e *Event) Key() (uint32) {
	return uint32(C.getKey(e))
}
