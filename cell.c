#include <stdlib.h>

#include "coords.h"
#include "boat.h"
#include "cell.h"

Cell makeCell(int shot, int state, Boat* boat){
	Cell new;
	new.shot = shot;
	new.state = state;
	new.ship = boat;
	return new;
}

void setCell(Cell* c, int shot, int state, Boat* boat){
	c -> shot = shot;
	c -> state = state;
	c -> ship = boat;
}

int getShot(Cell* c){
	return c -> shot;
}

void setShot(Cell* c, int value){
	c -> shot = value;
}

int getState(Cell* c){
	return c -> state;
}

void setState(Cell* c, int value){
	c -> state = value;
}

Boat* getBoat(Cell* c){
	return c -> ship;
}

void setBoat(Cell* c, Boat* boat){
	c -> ship = boat;
}
