all: main.o help.o
	gcc -o all main.o help.o

main.o : main.c help.h
	gcc -c main.c
help.o: help.c help.h
	gcc -c help.c

clean: 
	rm all main.o

