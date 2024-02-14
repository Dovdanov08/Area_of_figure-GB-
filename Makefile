#MAKEFILE
CC = gcc
CFLAGS = -c -o

all: area

area: main.o RootsArea.o
	$(CC) -o area main.o RootsArea.o

main.o: main.c RootsArea.h
	$(CC) $(CFLAGS) main.o main.c

RootsArea.o: RootsArea.c RootsArea.h
	$(CC)  $(CFLAGS) RootsArea.o RootsArea.c

clean:
	rm -rf *.o temp