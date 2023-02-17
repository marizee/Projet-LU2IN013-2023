CFLAGS=-Wall -Wextra

all: programme

programme : main.o polynome.o
	gcc $(CFLAGS) -o programme main.o polynome.o

main.o: main.c polynome.h
	gcc $(CFLAGS) -c main.c 

polynome.o: polynome.c polynome.h
	gcc $(CFLAGS) -c polynome.c 

clean:
	rm -f *.o programme
