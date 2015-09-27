CC=gcc
CFLAGS=-ggdb -Wall -std=gnu99 -pedantic
all: mysh

mysh: mysh.o alias.o command.o linkedList.o utility.o
	gcc -o mysh mysh.o alias.o command.o linkedList.o utility.o -lm

mysh.o: mysh.c mysh.h
	gcc -ggdb -c -o mysh.o mysh.c

alias.o: alias.c alias.h
	gcc -ggdb -c -o alias.o alias.c
	
command.o: command.c command.h
	gcc -ggdb -c -o command.o command.c

linkedList.o: linkedList.c linkedList.h
	gcc -ggdb -c -o linkedList.o linkedList.c
	
utility.o: utility.c utility.h
	gcc -ggdb -c -o utility.o utility.c
	
clean:
	rm *.o *~
