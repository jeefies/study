package sdl

/*
#include<SDL2/SDL.h>
 */
import "C"

// Surface Part
func (sur * Surface) FillRect(rect * Rect, color uint32) error {
	if (C.SDL_FillRect(sur, rect, C.Uint32(color)) != C.int(0)) {
		return NewSDLError("Could Not Fill Surface")
	}
	return nil
}

func (sur *Surface) Fill(rect * Rect, color uint32) error {
	return sur.FillRect(rect, color)
}

func (sur * Surface) Blit(src * Surface, place * Rect)  error {
    if C.SDL_BlitSurface(src, nil, sur, place) != C.int(0) {
        return NewSDLError("Could not apply surface into surface")
    }
    return nil
}

func (sur *Surface) Clear() error {
	return sur.FillRect(nil, 0)
}
