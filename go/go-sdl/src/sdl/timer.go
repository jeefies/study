package sdl

import (
    "os"
    "time"
)

/*
#include <SDL2/SDL.h>
*/
import "C"

// Timer
type TimerFunc func(uint32, interface{})(uint32)
var chans = make([]chan bool, 0)

func AddTimer(ms uint32, fnc TimerFunc, udata interface{}, tid * TimerID) {
	var ch = make(chan bool)
	*tid = uint64(len(chans))
	chans = append(chans, ch)
	var interval uint32 = ms
	for {
		select {
			case <-ch:
				ch <- true
				return
			default:
				interval = fnc(interval, udata)
				Delay(interval)
		}
	}
}

func RemoveTimer(id * TimerID) {
	var ch = chans[*id]
	ch <- false
	var timeout = make(chan bool, 1)

	go func() {
		time.Sleep(1e9)
		timeout <- true
	}()
	select {
		case <-ch:
			return
		case <- timeout:
			os.Stderr.WriteString("Could Not Remove Timer\n")
			os.Stderr.Sync()
	}
}

func Delay(ms uint32) {
	C.SDL_Delay(C.Uint32(ms))
}
