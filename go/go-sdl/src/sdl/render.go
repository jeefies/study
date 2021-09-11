package sdl

/*
#include<SDL2/SDL.h>
 */
import "C"

// const render create flags
const (
	RENDERER_SOFTWARE = C.SDL_RENDERER_SOFTWARE
	RENDERER_TARGETTEXTURE = C.SDL_RENDERER_TARGETTEXTURE
	RENDERER_PRESENTVSYNC = C.SDL_RENDERER_PRESENTVSYNC
	RENDERER_ACCELERATED = C.SDL_RENDERER_ACCELERATED
)

// Renderer Part
func CreateRenderer(win * Window, flags uint32) (ren *Renderer, err error) {
	ren = C.SDL_CreateRenderer(win, -1, C.Uint32(flags))
	if (ren == nil) {
		err = NewSDLError("Could Not Create renderer")
	}
	return
}

func (ren *Renderer) Close() {
	C.SDL_DestroyRenderer(ren)
}

func (ren *Renderer) FillSurface(sur * Surface, rect * Rect) error {
	text := C.SDL_CreateTextureFromSurface(ren, sur)
	if (text == nil) {
		return NewSDLError("Could Create Texture")
	}
	if (C.SDL_RenderCopy(ren, text, nil, rect) != C.int(0)) {
		return NewSDLError("Could not apply surface")
	}
	defer C.SDL_DestroyTexture(text)
	return nil
}

func (ren *Renderer) FillTexture(text *Texture, rect *Rect) error {
	if (C.SDL_RenderCopy(ren, text, nil, rect) != C.int(0)) {
		return NewSDLError("Could not apply texture")
	}
	return nil
}

func (ren *Renderer) CreateTextureFromSurface(sur *Surface) (text *Texture, err error) {
	text = C.SDL_CreateTextureFromSurface(ren, sur)
	if (text == nil) {
		err = NewSDLError("Could Create Texture")
		return
	}
	return
}

func (ren *Renderer) SetFillColor(r, g, b, a uint8) {
	C.SDL_SetRenderDrawColor(ren, C.uchar(r), C.uchar(g), C.uchar(b), C.uchar(a))
}

func (ren *Renderer) DrawRect(rect * Rect) {
	C.SDL_RenderDrawRect(ren, rect)
}

func (ren *Renderer) FillRect(rect * Rect) {
	C.SDL_RenderFillRect(ren, rect)
}

func (ren *Renderer) DrawLine(pos1, pos2 Position) {
	C.SDL_RenderDrawLine(ren, C.int(pos1.X), C.int(pos1.Y), C.int(pos2.X), C.int(pos2.Y))
}

func (ren *Renderer) DrawPoint(pos Position) {
	C.SDL_RenderDrawPoint(ren, C.int(pos.X), C.int(pos.Y))
}

func (ren *Renderer) Present(){
	C.SDL_RenderPresent(ren)
}

func (ren *Renderer) Clear() {
	C.SDL_RenderClear(ren)
}
