CFLAGS=-Wall -Wextra
all: programme

programme : main.o polynome.o structure.o
	gcc $(CFLAGS) -o programme main.o polynome.o structure.o div_euclidienne.o congruence.o -lm

structure.o: structure.c structure.h
	gcc $(CFLAGS) -c structure.c

polynome.o: polynome.c polynome.h structure.h
	gcc $(CFLAGS) -c polynome.c 

main.o: main.c polynome.h structure.h
	gcc $(CFLAGS) -c main.c 
	
congruence.o: congruence.c congruence.h
	gcc $(CFLAGS) -c congruence.c

div_euclidienne.o: div_euclidienne.c div_euclidienne.h polynome.h structure.h
	gcc $(CFLAGS) -c div_euclidienne.c
	
clean:
	rm -f *.o programme
