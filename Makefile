CC=gcc
CFLAGS=-std=c99 -Wpedantic -Wall -Wextra

all: battleship

battleship: battleship.c global_var.o coords.o boat.o board.o utils.o
	$(CC) -o battleship.o battleship.c -c $(CFLAGS)
	$(CC) -o battleship *.o
	rm -f *.o

global_var.o: global_var.c global_var.h
	$(CC) -o global_var.o global_var.c -c $(CFLAGS)

coords.o: coords.c coords.h
	$(CC) -o coords.o coords.c -c $(CFLAGS)

boat.o: boat.c boat.h coords.h
	$(CC) -o boat.o boat.c -c $(CFLAGS)

board.o: board.c board.h global_var.h coords.h boat.h
	$(CC) -o board.o board.c -c $(CFLAGS)

utils.o: utils.c utils.h global_var.h coords.h boat.h board.h
	$(CC) -o utils.o utils.c -c $(CFLAGS)

clean:
	rm -f *.o battleship
