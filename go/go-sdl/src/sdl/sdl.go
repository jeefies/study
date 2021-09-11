package sdl

/*
#include<SDL2/SDL.h>
 */
import "C"

const (
	INIT_TIMER uint32	= 0x000000001
	INIT_AUDIO uint32	= 0x000000010
	INIT_VIDEO uint32	= 0x000000020
	INIT_JOYSTICK uint32	= 0x000000200
	INIT_HAPTIC uint32	= 0x000001000
	INIT_GAMECONTROLLER uint32 = 0x00000200
	INIT_EVENTS uint32	= 0x000004000
	INIT_SENSOR uint32	= 0x000008000
	INIT_EVERYTHING uint32	= (INIT_TIMER | INIT_AUDIO | INIT_VIDEO | INIT_JOYSTICK | INIT_HAPTIC | INIT_GAMECONTROLLER | INIT_EVENTS | INIT_SENSOR)
	INIT_DEFAULT uint32	= (INIT_TIMER | INIT_AUDIO | INIT_VIDEO | INIT_EVENTS)
)

func Init(flags uint32) error {
	if (C.SDL_Init(C.Uint32(flags)) != 0) {
		return NewSDLError("Could Not Init SDL")
	}
	return nil
}

func Quit() {
	C.SDL_Quit()
}