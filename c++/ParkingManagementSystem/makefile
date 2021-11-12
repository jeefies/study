CC = gcc
WCC = x86_64-w64-mingw-gcc

SRC = ./src
BUILD = ./build
BIN = .
INC = ./include

all: main.o
	$(CC) $^ -o $(BIN)/main.exe

main.o: $(SRC)/main.c $(INC)/system.h
	$(CC) $(SRC)/main.c -I$(INC)
