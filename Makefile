CC=gcc
CFLAGS=-std=c99 -Wpedantic -Wall -Wextra -D QUAD -g

all: battleship

battleship: battleship.c global_var.o coords.o boat.o board.o utils.o cell.o point.o qtree.o
	$(CC) -o battleship.o battleship.c -c $(CFLAGS)
	$(CC) -o battleship *.o
	rm -f *.o

global_var.o: global_var.c global_var.h
	$(CC) -o global_var.o global_var.c -c $(CFLAGS)

coords.o: coords.c coords.h
	$(CC) -o coords.o coords.c -c $(CFLAGS)

cell.o: cell.c cell.h
	$(CC) -o cell.o cell.c -c $(CFLAGS)

point.o: point.c point.h
	$(CC) -o point.o point.c -c $(CFLAGS)

qtree.o: qtree.c qtree.h
	$(CC) -o qtree.o qtree.c -c $(CFLAGS)

boat.o: boat.c boat.h coords.h
	$(CC) -o boat.o boat.c -c $(CFLAGS)

board.o: board.c board.h global_var.h coords.h boat.h
	$(CC) -o board.o board.c -c $(CFLAGS)

utils.o: utils.c utils.h
	$(CC) -o utils.o utils.c -c $(CFLAGS)

clean:
	rm -f *.o battleship
