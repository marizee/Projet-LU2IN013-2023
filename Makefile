CFLAGS=-Wall -Wextra
all: programme

programme : main.o polynome.o structure.o div_euclidienne.o
	gcc $(CFLAGS) -o programme main.o polynome.o structure.o div_euclidienne.o -lm
programme1 : test.o
	gcc $(CFLAGS) -o programme1 test.o
programme2 : test2.o
	gcc $(CFLAGS) -o programme1 test2.o
test.o: test.c
	gcc $(CFLAGS) -c test.c
test2.o: test2.c
	gcc $(CFLAGS) -c test2.c
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
