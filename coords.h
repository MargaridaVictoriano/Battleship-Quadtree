#ifndef COORDS
#define COORDS


typedef struct {
	int row;
	int column;
	int rotation;
} Coords;

Coords* buildCoords(int,int,int);
void destroyCoords(Coords*);

#endif
