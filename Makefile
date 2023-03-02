CFLAGS=-Wall -Wextra
all: programme

programme : main.o polynome.o structure.o
	gcc $(CFLAGS) -o programme main.o polynome.o structure.o -lm

structure.o: structure.c structure.h
	gcc $(CFLAGS) -c structure.c

polynome.o: polynome.c polynome.h structure.h
	gcc $(CFLAGS) -c polynome.c 

main.o: main.c polynome.h structure.h
	gcc $(CFLAGS) -c main.c 

clean:
	rm -f *.o programme
