CC = gcc
FLAGS = -Wall -g

StrList: Main.o StrList.o
	$(CC) $(FLAGS) -o StrList StrList.o Main.o

StrList.o: StrList.c StrList.h
	$(CC) $(FLAGS) -c StrList.c -o StrList.o

Main.o: Main.c StrList.h
	$(CC) $(FLAGS) -c Main.c -o Main.o

.PHONY: all clean

all: StrList

clean:
	rm -f *.o *.a *.so StrList Main 
