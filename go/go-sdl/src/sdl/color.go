package sdl

/*
#include<SDL2/SDL.h>
 */
import "C"

// RGB Color Part
func MapRGB(sur *Surface, r, g, b uint8) uint32 {
	var color MapColor = C.SDL_MapRGB(sur.format, C.Uint8(r), C.Uint8(g), C.Uint8(b))
	return uint32(color)
}

func MapRGBA(sur *Surface, r, g, b, a uint8) uint32 {
	var color MapColor = C.SDL_MapRGBA(sur.format, C.Uint8(r), C.Uint8(g), C.Uint8(b), C.Uint8(a))
	return uint32(color)
}

func NewColor(r, g, b uint8) (*Color) {
    return &Color{C.Uint8(r), C.Uint8(g), C.Uint8(b), C.Uint8(255)}
}
