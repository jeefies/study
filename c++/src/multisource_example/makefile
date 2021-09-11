all: main.c call.o
	gcc main.c call.o -o main

call.o: call.c
	gcc -c call.c

clean:
	rm *.o main
