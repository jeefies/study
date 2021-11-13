CC = gcc
WCC = x86_64-w64-mingw-gcc

SRC = ./src
BUILD = ./build
BIN = .
INC = ./include

CFLAGS = -g

all: $(BUILD)/main.o $(BUILD)/person.o $(BUILD)/parkinglot.o
	$(CC) $^ -o $(BIN)/main.exe $(CFLAGS)

$(BUILD)/main.o: $(SRC)/main.c $(INC)/parksys.h
	$(CC) -c $(SRC)/main.c -I$(INC) -o $@ $(CFLAGS)

$(BUILD)/person.o: $(SRC)/person.c $(INC)/parksys.h
	$(CC) -c $(SRC)/person.c -I$(INC) -o $@ $(CFLAGS)

$(BUILD)/parkinglot.o: $(SRC)/parkinglot.c $(INC)/parksys.h
	$(CC) -c $(SRC)/parkinglot.c -I$(INC) -o $@ $(CFLAGS)

clean:
	rm -rf $(BUILD)/*.o
