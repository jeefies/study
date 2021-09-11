CC = gcc

SRC_PATH = .
JSND_PATH = $(SRC_PATH)/jsnd
INCLUDE_PATH = ./include
BUILD_PATH = ./_build

HEADERS = $(INCLUDE_PATH)/jplayer.h $(INCLUDE_PATH)/wins.h $(INCLUDE_PATH)/vars.h

CFLAGS = -g -Wall

SDL_LD = `pkg-config SDL2_mixer SDL2_ttf --cflags --libs`

jplayer.exe: $(BUILD_PATH)/jplayer.o $(BUILD_PATH)/wins.o $(BUILD_PATH)/jsnd.o $(BUILD_PATH)/snd.o $(BUILD_PATH)/askfile.o $(HEADERS)
	$(CC) $(BUILD_PATH)/jplayer.o $(BUILD_PATH)/wins.o $(BUILD_PATH)/jsnd.o $(BUILD_PATH)/snd.o \
		$(BUILD_PATH)/askfile.o \
		-I$(INCLUDE_PATH) -o bin/$@ \
	   	$(SDL_LD) $(CFLAGS)

$(BUILD_PATH)/snd.o: $(SRC_PATH)/snd.c $(HEADERS)
	$(CC) -c $(SRC_PATH)/snd.c -o $@ $(CFLAGS) -I$(INCLUDE_PATH) $(SDL_LD)

$(BUILD_PATH)/wins.o: $(SRC_PATH)/wins.c $(HEADERS)
	$(CC) -c $(SRC_PATH)/wins.c -o $@ $(SDL_LD) $(CFLAGS) -I$(INCLUDE_PATH)

$(BUILD_PATH)/jplayer.o: $(SRC_PATH)/jplayer.c $(HEADERS)
	$(CC) -c $(SRC_PATH)/jplayer.c -o $@ $(SDL_LD) $(CFLAGS)

$(BUILD_PATH)/jsnd.o: $(JSND_PATH)/jsnd.c $(JSND_PATH)/jsnd.h
	$(CC) -c $(JSND_PATH)/jsnd.c -o $@ $(CFLAGS) -I$(JSND_PATH)

$(BUILD_PATH)/askfile.o: $(SRC_PATH)/askfile.c $(INCLUDE_PATH)/askfile.h
	$(CC) -c $(SRC_PATH)/askfile.c -o $@ $(SDL_LD) -I$(INCLUDE_PATH)


clean:
	rm -rf bin/*.exe $(BUILD_PATH)/*.o
