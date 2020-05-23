#include <stdlib.h>

#include "coords.h"

/**
* Function name : buildCoords()
* Usage         : buildCoords(int,int,int);
* Definition    : This function creates the coordinates that represent
*                 the bitmap piece.
*/

Coords* buildCoords(int row, int column, int rotation) {
  Coords* new = (Coords *)malloc(sizeof(Coords));
  if(new == NULL) exit(-1);
  new -> row = row;
  new -> column = column;
  new -> rotation = rotation % 360;
  return new;
}

/**
* Function name : destroyCoords()
* Usage         : destroyCoords(Coords*);
* Definition    : This function destroys the coordinates that represent
*                 the bitmap piece.
*/

void destroyCoords(Coords* new) {
  free(new);
}
