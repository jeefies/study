package main

import (
	"os"
	"strconv"
	"math/rand"
	"time"
)

import "sdl"
import "sdl/ttf"

const sqrL int = 12
const (
	LEFT = -2
	RIGHT = 2
	UP = -1
	DOWN = 1
)

var stdout = os.Stdout
var prints = stdout.WriteString

var stop bool = false
var failed bool = false
var timerid = new(sdl.TimerID)
var pos = make([]sdl.Position, 1)
var direct = LEFT
var food_pos = sdl.Position{0, 0}

var win *sdl.Window
var ren *sdl.Renderer
var sur *sdl.Surface


func check(err error) {
    if (err != nil) {
        panic(err)
    }
}

func new_food(first bool) {
	rand.Seed(time.Now().UnixNano())
	rect := sdl.NewRect(0, 0, sqrL, sqrL)
	rect.FromPos(food_pos)
	if (first) {
		sur.FillRect(rect, sdl.MapRGB(sur, 0, 0, 0))
	} else {
		sur.FillRect(rect, sdl.MapRGB(sur, 255, 255, 255))
	}
	food_pos.X = rand.Intn(800 / sqrL - 1) * sqrL + 400 % sqrL
	food_pos.Y = rand.Intn(450 / sqrL - 1) * sqrL + 225 % sqrL
	rect.FromPos(food_pos)
	sur.FillRect(rect, sdl.MapRGB(sur, 255, 0, 0))

	// fmt.Printf("food pos: x = %d, y = %d\n", food_pos.X, food_pos.Y)
}

func main() {
	var err error

	err = sdl.Init(sdl.INIT_DEFAULT)
	if (err != nil) {
		panic(err)
	}
	defer sdl.Quit()

	win, err = sdl.CreateWindow("Hello World", 800, 450, sdl.WINPOS_CENTERED, sdl.WINPOS_CENTERED)
	if (err != nil) {
		panic(err)
	}
	defer win.Close()

	ren, err = sdl.CreateRenderer(win, sdl.RENDERER_PRESENTVSYNC)
	if (err != nil) {
		panic(err)
	}
	defer ren.Close()

	w, h := win.GetSize()
	prints("size:")
	prints(strconv.Itoa(w))
	prints(", ")
	prints(strconv.Itoa(h))
	prints("\n")
	stdout.Sync()

	fail := func() {
		stop = true
		ren.SetFillColor(255, 0, 0, 255)
		ren.Clear()

		sur.Fill(nil, 0)
		ft, err := ttf.OpenFont("font.ttf", 36) // 48px
		check(err)
		fg := *sdl.NewColor(255, 255, 255)
		r := sdl.NewRect(300, 201, 0, 0)

		tsur, err := ft.RenderQuick("You Failed!", fg)
		check(err)

		// ttext, err := ren.CreateTextureFromSurface(tsur)
		// check(err)
		// ren.FillTexture(ttext, r)
		sur.Blit(tsur, r)
		err = ren.FillSurface(tsur, r)
		check(err)
		ren.Present()

		ren.SetFillColor(0, 0, 0, 0)

		sdl.Delay(2000)

		ren.Clear()
		sur.Clear()

		pos = pos[:1]
		stop = false
		pos[0] = sdl.Position{w/10*5, h/10*5}
		direct = LEFT
		new_food(true)
	}

	defer func() {
		if err_ := recover(); err_ != nil {
			prints(err.Error())
		}
	}()

	sur = win.GetSurface()
	sur.FillRect(nil, 0)

	e := sdl.NewEvent()

	timerfunc := func(interval uint32, param interface{}) (uint32) {
		ren.Clear()
		l := len(pos) - 1
		// Next rect
		p := pos[l]
		if (p.X < 0 || p.X >= w || p.Y < 0 || p.Y >= h) {
			prints("Failed\n")
			failed = true
		}
		np := sdl.Position{p.X, p.Y}

		if (stop) {
			goto __draw_rect
		}
		switch direct {
			case UP:
				np.Y -= sqrL
			case DOWN:
				np.Y += sqrL
			case LEFT:
				np.X -= sqrL
			case RIGHT:
				np.X += sqrL
		}
		// fmt.Printf("snake pos: x = %d, y = %d\n", np.X, np.Y)
		for _, _p := range pos {
			if _p.Equal(np) {
				failed = true
				break
			}
		}
		pos = append(pos, np)

		if (failed) {
			fail()
			failed = false
			return interval
		}


		__draw_rect:
		rect := sdl.NewRect(0, 0, sqrL, sqrL)
		rect.FromPos(food_pos);
		sur.FillRect(rect, sdl.MapRGB(sur, 255, 0, 0))

		rect.FromPos(pos[0])
		err = sur.FillRect(rect, 0)
		check(err)
		if (!np.Equal(food_pos)) {
			if (!stop) {
				pos = pos[1:]
			}
		} else {
			new_food(false)
		}
		rect.FromPos(pos[l])
		err = sur.FillRect(rect, sdl.MapRGB(sur, 255, 255, 255))
		check(err)

		err = ren.FillSurface(sur, nil)
		check(err)

		ren.Present()
		return interval
	}

	pos[0] = sdl.Position{w/10*5, h/10*5}
	go sdl.AddTimer(1000/16, timerfunc, nil, timerid)
	defer sdl.RemoveTimer(timerid)

	new_food(true)
	for {
		for e.Poll() {
			switch e.Type() {
				case sdl.QUIT:
					goto __quit
				case sdl.KEYDOWN:
					switch e.Key() {
						case 'w', sdl.KUP:
							if (direct == -UP) {
								failed = true
							}
							direct = UP
						case 's', sdl.KDOWN:
							if (direct == UP) {
								failed = true
							}
							direct = DOWN
						case 'a', sdl.KLEFT:
							if (direct == -LEFT) {
								failed = true
							}
							direct = LEFT
						case 'd', sdl.KRIGHT:
							if (direct == LEFT) {
								failed = true
							}
							direct = RIGHT
						case sdl.KESC:
							goto __quit
						case ' ':
							stop = !stop
					}
			}
		}
		sdl.Delay(20)
	}

	__quit:
	prints("")
}
