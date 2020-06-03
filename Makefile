CC=gcc
CFLAGS=-std=c99 -Wpedantic -Wall -Wextra
LDFLAGS=-lm -lpthread -lrt
QUAD=-D QUAD

all: matrix

quad: clean battleship.c global_var.h coords.h boat.h board.h utils.h cell.h point.h qtree.h
	@$(CC) battleship.c global_var.c coords.c boat.c board.c utils.c cell.c point.c qtree.c $(CFLAGS) $(QUAD) $(LDFLAGS) -o battleship

matrix: clean battleship.c global_var.h coords.h boat.h board.h utils.h cell.h
	@$(CC) battleship.c global_var.c coords.c boat.c board.c utils.c cell.c $(CFLAGS) $(LDFLAGS) -o battleship

clean:
	@rm -f *.o battleship file
