#ifndef CELL
#define CELL

typedef struct {
	char shot;
	char state;
	Boat *ship;
} Cell;

Cell makeCell(int,int,Boat*);
void setCell(Cell*,int,int,Boat*);
int getShot(Cell*);
void setShot(Cell*,int);
int getState(Cell*);
void setState(Cell*,int);
Boat* getBoat(Cell*);
void setBoat(Cell*,Boat*);

#endif
