CC= gcc
FLAGS= -Wall -g

all: StrList

StrList: main.o
	$(CC) -o StrList main.o

StrList.o: StrList.h
	$(CC) -c $(FLAGS) -fPIC StrList.c	

main.o: main.c StrList.h 
	$(CC)  -c $(FLAGS) -fPIC main.c

.PHONY: clean all

clean:
	rm -f *.o *.a *.so StrList main