#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "global_var.h"
#include "coords.h"
#include "boat.h"
#include "board.h"
#include "utils.h"

/**
* Function name : buildBoard()
* Usage         : buildBoard();
* Definition    : This function builds,initializes the game board and then it
* 								returns the new board.
*/

Board *buildBoard() {
	Board *new = (Board *)malloc(sizeof(Board)); //players map
	if(new == NULL) exit(-1);

	new -> remainingBoats = 0;

	new -> map = (Cell *)malloc(n_matrix*n_matrix*sizeof(Cell));
	if(new -> map == NULL) exit(-1);

	for(int i = 0; i <n_matrix; i++) {
		for(int j = 0; j <n_matrix; j++) {
			new -> map[i*n_matrix + j].shot = 0;
			new -> map[i*n_matrix + j].state = 0;
			new -> map[i*n_matrix + j].ship = NULL;
		}
	}

	new -> size_boats = 0;
	new -> boats = (Boat **)malloc(sum_boats*sizeof(Boat *));
	if(new -> boats == NULL) exit(-1);

	return new;
}

/**
* Function name : destroyBoard()
* Usage         : destroyBoard(Board*);
* Definition    : This function destroys the game board.
*/

void destroyBoard(Board* map) {
	free(map -> map);

	for(int i=0; i< map -> size_boats; i++){
		destroyBoat(map -> boats[i]);
	}
	free(map -> boats);

	free(map);
}

/**
* Function name : containsBoat()
* Usage         : containsBoat(Board*,int,int);
* Definition    : This function verifies if a cell is occupied by a boat.
*/

bool containsBoat(Board* board, int x, int y) {
	if(board -> map[x*n_matrix + y].ship != NULL) return true;
	return false;
}

/**
* Function name : insertBoat()
* Usage         : insertBoat(Board*,char,Coords*);
* Definition    : This function inserts the given boat in the game board.
*/

void insertBoat(Board* board, char boatId, Coords* coords) {
	int x = coords -> row;
	int y = coords -> column;

	Boat* temp = buildBoat(boatId,coords);
	board -> boats[board -> size_boats] = temp;
	board -> size_boats++;

	if(boatId == 'l') {
		for(int i = 0 ; i < BITMAP_SIZE ; i++) {
			for(int j = 0; j < BITMAP_SIZE; j++) {
				if(temp -> ship[i*BITMAP_SIZE + j] == 1) {
					board -> map[(i+x) * n_matrix + (j+y)].state = 1;
					board -> map[(i+x) * n_matrix + (j+y)].ship = temp;
				}
			}
		}
	}
	else {
		int boatSize = temp -> hp;
		if(coords->rotation % 180 == 0) { //Horizontal
			for(int k = y; k < boatSize + y; k++) {
				board -> map[x * n_matrix + k].state = 1;
				board -> map[x * n_matrix + k].ship = temp;
			}
		}
		else { //Vertical
			for(int k = x; k < boatSize + x; k++) {
				board -> map[k * n_matrix + y].state = 1;
				board -> map[k * n_matrix + y].ship = temp;
			}

		}
	}
}

/**
* Function name : isAvailablePosition()
* Usage         : isAvailablePosition(Board*,char,Coords*);
* Definition    : This functions checks if a given boat can be placed on the board.
*/

bool isAvailablePosition(Board* board, char boatId, Coords* coords) {
	int x = coords -> row;
	int y = coords -> column;
	int rotation = coords -> rotation;

	if (x < 0 || y < 0 || x >= n_matrix || y >= n_matrix || rotation < 0 || rotation > 360 || rotation%90 != 0) return false;
	if (boatId == 'l') {
		if (BITMAP_SIZE + x > n_matrix || BITMAP_SIZE + y > n_matrix) return false;
		Boat* temp = buildBoat(boatId,coords);
		for(int i = 0 ; i < BITMAP_SIZE; i++) {
			for(int j = 0; j < BITMAP_SIZE; j++) {
				if(temp -> ship[i*BITMAP_SIZE + j] == 1) {
					if(i+x < 0 || j+y < 0 || i+x >= n_matrix || j+y >= n_matrix || containsBoat(board,i+x,j+y)) {
						destroyTempBoat(temp);
						return false;
					}
				}
			}
		}
		destroyTempBoat(temp);
		return true;
	}
	else {
		int size = boatSize(boatId);
		if(coords->rotation % 180 == 0) { //Horizontal
			if (size + y >= n_matrix) return false;
			for(int k = y; k < size + y; k++) {
				if(containsBoat(board,x,k)) return false;
			}
		}
		else { //Vertical
			if(size + x >= n_matrix) return false;
			for(int k = x; k < size + x; k++) {
				if(containsBoat(board,k,y)) return false;
			}

		}
		return true;
	}
}

/**
* Function name : randomlyPlaceBoatonBoard()
* Usage         : randomlyPlaceBoatonBoard(Board*);
* Definition    : This function generates the boat coordinates randomly and inserts the boat
*								 on the game board.
*/

void randomlyPlaceBoatonBoard(Board* board) {
	for (int i = 0; i < n_boats; i++) {
		char id = listBoat[i];
		int x,y,rot,n = boat_number[i];
		while(n > 0){
			if(id == 'l'){
				x = getRandomNumber(0, n_matrix-5);
				y = getRandomNumber(0, n_matrix-5);
			}
			else {
				x = getRandomNumber(0, n_matrix-1);
				y = getRandomNumber(0, n_matrix-1);
			}
			rot = getRandomNumber(0, 3)*90;

			Coords* coords = buildCoords(x,y,rot);
			if (isAvailablePosition(board, id, coords)) {
				insertBoat(board, id, coords);
				n--;
			}
			else destroyCoords(coords);
		}
	}
}


/**
* Function name : selectCharDefense()
* Usage         : selectCharDefense(char);
* Definition    : Returns the corresponding symbol.
*/

char selectCharDefense(char v){
	switch(v){
		case 0 : return '~';
		case 1 : return '#';
		case 2 : return 'X';
		case 3 : return 'O';
		default: return -1;
	}
}

/**
* Function name : selectCharAttack()
* Usage         : selectCharAttack(char);
* Definition    : Returns the corresponding symbol.
*/

char selectCharAttack(char v){
	switch(v){
		case 0 : return '~';
		case 1 : return 'O';
		case 2 : return 'X';
		default: return -1;
	}
}

/**
* Function name : printDefenseBoard()
* Usage         : printDefenseBoard(Board*);
* Definition    : This function displays the defense map.
*/

void printDefenseBoard(Board* map){
	printf("   ");
	for(int i=0; i<n_matrix; i++){
		printf(" %2d",i);
	}
	printf("\n");

	for(int i=0; i<n_matrix; i++){
		printf(" %2d",i);
		for(int j=0; j<n_matrix; j++){
			int temp = map -> map[i*n_matrix + j].state;
			printf("  %c",selectCharDefense(temp));
		}
		printf("\n");
	}
}

/**
* Function name : printAttackBoard()
* Usage         : printAttackBoard(Board*);
* Definition    : This function displays the attack map.
*/

void printAttackBoard(Board* map) {
	printf("   ");
	for(int i=0; i<n_matrix; i++){
		printf(" %2d",i);
	}
	printf("\n");

	for(int i=0; i<n_matrix; i++){
		printf(" %2d",i);
		for(int j=0; j<n_matrix; j++){
			int temp = map -> map[i*n_matrix + j].shot;
			printf("  %c",selectCharAttack(temp));
		}
		printf("\n");
	}
}
