package sdl

/*
#cgo CFLAGS: -I../../include
#cgo LDFLAGS: -L../../lib -lSDLg
#include <SDL2/SDL.h>

typedef unsigned long TimerID;

typedef struct TimerParam {
	Uint32 interval;
	Uint32(* func)(Uint32, void*);
	void * param;
} TimerParam;
*/
import "C"

type Window = C.SDL_Window
type Renderer = C.SDL_Renderer
type Surface = C.SDL_Surface
type Texture = C.SDL_Texture
type Color = C.SDL_Color
type Rect = C.SDL_Rect
type MapColor = C.Uint32
type PixelFormat = C.SDL_PixelFormat
type Event = C.SDL_Event
// type TimerID = C.TimerID
type TimerID = uint64

type Position struct {
	X int
	Y int
}

func (pos Position) Equal(p Position) bool {
	return pos.X == p.X && pos.Y == p.Y
}


type SDLError struct {
	errormsg string
}

func (sdle *SDLError) Error() string{
	oe := C.GoString(C.SDL_GetError())
	return sdle.errormsg + " : " + oe
}

func NewSDLError(msg string) error {
	return &SDLError{msg}
}
