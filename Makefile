all: programme

programme : main.o polynome.o
	gcc -Wall -o programme main.o polynome.o

main.o: main.c polynome.h
	gcc -Wall -c main.c 

polynome.o: polynome.c polynome.h
	gcc -Wall -c polynome.c 

clean:
	rm -f *.o programme