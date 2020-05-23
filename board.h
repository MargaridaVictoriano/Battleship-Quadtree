#ifndef BOARD
#define BOARD

//Matrix limits
#define MIN_MATRIX 20
#define MAX_MATRIX 40

#ifdef QUAD

#include "qtree.h"

typedef struct {
	QD_Node *qtree;
	char remainingBoats;
	unsigned char size_boats;
	Boat **boats;
} Board;

#else

#include "cell.h"

typedef struct {
	Cell *map;
	char remainingBoats;
	unsigned char size_boats;
	Boat **boats;
} Board;

#endif

Board* buildBoard();
void destroyBoard(Board*);
bool containsBoat(Board*,int,int);
void insertBoat(Board*,char,Coords*);
bool isAvailablePosition(Board*,char,Coords*);
void randomlyPlaceBoatonBoard(Board*);
char selectCharDefense(char);
char selectCharAttack(char);
void printDefenseBoard(Board*);
void printAttackBoard(Board*);
Cell* getCell(Board*,int,int);

#endif
