CC= gcc
FLAGS= -Wall -g

all: StrList 

StrList: Main.o
	$(CC) -o StrList Main.o

StrList.o: StrList.h
	$(CC) -c $(FLAGS) -fPIC StrList.c	

Main.o: Main.c StrList.h 
	$(CC)  -c $(FLAGS) -fPIC Main.c

.PHONY: clean all

clean:
	rm -f *.o *.a *.so StrList Main 