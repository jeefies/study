all:
	@GOPATH=`pwd` go build sdl
	@echo "Build SDLg"
	@GOPATH=`pwd` go build sdl/ttf
	@echo "Build SDLg/TTF"
	@GOPATH=`pwd` go build -gcflags "-N -l" main
	@mv ./main ./bin/main
	@echo "Build Finish"

test:
	@GOPATH=`pwd` go build -gcflags "-N -l" sdl
	@GOPATH=`pwd` go build -gcflags "-N -l" main
	@mv ./main ./test
	@echo "Test build"
