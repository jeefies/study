CC=gcc

FLAGS = -lSDL2

window.exe: window.o
	gcc $^ -o $@ $(FLAGS)

window.o: window.c
	gcc -c $^ -o $@ $(FLAGS)

clean:
	rm window.exe *.o
