package sdl

/*
#include<SDL2/SDL.h>
 */
import "C"

// Rect part
func NewRect(x, y, w, h int) (*Rect) {
	return &Rect{C.int(x), C.int(y), C.int(w), C.int(h)}
}

func (r * Rect) FromPos(pos Position) {
	r.x, r.y = C.int(pos.X), C.int(pos.Y)
}
