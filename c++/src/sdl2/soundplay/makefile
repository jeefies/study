FLAGS=-lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

CC=gcc

play.exe: play.o
	$(CC) $^ -o $@ $(FLAGS)

play.o: play.c
	$(CC) -c $^ $(FLAGS) -o $@

clean:
	rm play.exe *.o -rf
