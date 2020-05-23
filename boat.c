#include <stdlib.h>

#include "coords.h"
#include "boat.h"

const char listBoat[] = {'l','c','b','r','s','d'};

const char l[] = "LBOAT";
const char c[] = "CARRIER";
const char b[] = "BATTLESHIP";
const char r[] = "CRUISER";
const char s[] = "SUBMARINE";
const char d[] = "DESTROYER";

/**
* Function name : indexBoat()
* Usage         : indexBoat(char);
* Definition    : Returns boat ID index.
*/

signed char indexBoat(char id){
  switch(id){
    case 'l': return 0;
    case 'c': return 1;
    case 'b': return 2;
    case 'r': return 3;
    case 's': return 4;
    case 'd': return 5;
    default: return -1;
  }
}

/**
* Function name : boatSize()
* Usage         : boatSize(char);
* Definition    : Returns the boat size.
*/

signed char boatSize(char id){
  switch(id){
    case 'l': return 9;
    case 'c': return 5;
    case 'b': return 4;
    case 'r': return 3;
    case 's': return 3;
    case 'd': return 2;
    default: return -1;
  }
}

/**
* Function name : boatName()
* Usage         : boatName(char);
* Definition    : Returns the boat name.
*/

const char* boatName(char id){
  switch(id){
    case 'l': return l;
    case 'c': return c;
    case 'b': return b;
    case 'r': return r;
    case 's': return s;
    case 'd': return d;
    default: return NULL;
  }
}

/**
* Function name : boatRot()
* Usage         : boatRot(Boat*);
* Definition    : This function applies the desired rotation to the boat.
*/

void boatRot(Boat* boat){
  char *mat = boat -> ship, temp;
  switch(boat -> coords -> rotation){
    case 0 :
    return;
    case 90:
    for (int i = 0; i < BITMAP_SIZE / 2; i++) {
      for (int j = i; j < BITMAP_SIZE-i-1; j++) {
        temp = mat[i*BITMAP_SIZE + j];
        mat[i*BITMAP_SIZE + j] = mat[j*BITMAP_SIZE + BITMAP_SIZE-1-i];
        mat[j*BITMAP_SIZE + BITMAP_SIZE-1-i] = mat[(BITMAP_SIZE-1-i)*BITMAP_SIZE + BITMAP_SIZE-1-j];
        mat[(BITMAP_SIZE-1-i)*BITMAP_SIZE + BITMAP_SIZE-1-j] = mat[(BITMAP_SIZE-1-j)*BITMAP_SIZE + i];
        mat[(BITMAP_SIZE-1-j)*BITMAP_SIZE + i] = temp;
      }
    }
    return;
    case 180:
    for(int i=0;i<BITMAP_SIZE/2;i++) {
      for(int j=0;j<BITMAP_SIZE;j++) {
        temp = mat[i*BITMAP_SIZE + j];
        mat[i*BITMAP_SIZE + j] = mat[(BITMAP_SIZE-i-1)*BITMAP_SIZE + BITMAP_SIZE-j-1];
        mat[(BITMAP_SIZE-i-1)*BITMAP_SIZE + BITMAP_SIZE-j-1] = temp;
      }
    }

    // When BITMAP_SIZE odd
    if(BITMAP_SIZE & 1){
      for(int j=0; j<BITMAP_SIZE/2; j++){
        temp = mat[(BITMAP_SIZE/2)*BITMAP_SIZE + j];
        mat[(BITMAP_SIZE/2)*BITMAP_SIZE + j] = mat[(BITMAP_SIZE/2)*BITMAP_SIZE + BITMAP_SIZE-j-1];
        mat[(BITMAP_SIZE/2)*BITMAP_SIZE + BITMAP_SIZE-j-1] = temp;
      }
    }

    return;
    case 270:
    for (int i = 0; i < BITMAP_SIZE / 2; i++) {
      for (int j = i; j < BITMAP_SIZE-i-1; j++) {
        temp = mat[i*BITMAP_SIZE + j];
        mat[i*BITMAP_SIZE + j] = mat[(BITMAP_SIZE-1-j)*BITMAP_SIZE + i];
        mat[(BITMAP_SIZE-1-j)*BITMAP_SIZE + i] = mat[(BITMAP_SIZE-1-i)*BITMAP_SIZE + BITMAP_SIZE-1-j];
        mat[(BITMAP_SIZE-1-i)*BITMAP_SIZE + BITMAP_SIZE-1-j] = mat[j*BITMAP_SIZE + BITMAP_SIZE-1-i];
        mat[j*BITMAP_SIZE + BITMAP_SIZE-1-i] = temp;
      }
    }
    return;
  }
}

/**
* Function name : prepareBoat()
* Usage         : prepareBoat(Boat*);
* Definition    : This function creates the boat generic model.
*/

void prepareBoat(Boat* boat){
  char id = boat -> id;
  if(id == 'l') {
    for(int i=0; i<BITMAP_SIZE ; i++)
    boat -> ship[i*BITMAP_SIZE + 0] = 1;
    for(int i=1; i<BITMAP_SIZE ; i++)
    boat -> ship[(BITMAP_SIZE-1)*BITMAP_SIZE + i] = 1;
  }
  else {
    int size = boatSize(id);
    for(int i=0; i<size; i++){
      boat -> ship[2*BITMAP_SIZE + i] = 1;
    }
  }
}

/**
* Function name : buildBoat()
* Usage         : buildBoat(char,Coords*);
* Definition    : This function allocates the structure on the heap,
*                 creates the boat generic model
*                 and it applies the requested rotation.
*                 Returns a boat.
*/

Boat* buildBoat(char id, Coords* coords){
  Boat* new = (Boat*)malloc(sizeof(Boat));
  if(new == NULL) exit(-1);

  new -> id = id;
  new -> coords = coords;
  new -> hp = boatSize(id);

  new -> ship = (char *)malloc(BITMAP_SIZE*BITMAP_SIZE*sizeof(char));
  if(new -> ship == NULL) exit(-1);

  for(int i=0; i<BITMAP_SIZE; i++){
    for(int j=0; j<BITMAP_SIZE; j++){
      new -> ship[i*BITMAP_SIZE + j] = 0;
    }
  }

  prepareBoat(new);
  boatRot(new);
  return new;
}

/**
* Function name : destroyTempBoat()
* Usage         : destroyTempBoat(Boat*);
* Definition    : This function deallocs everything except for the coordinates.
*/

void destroyTempBoat(Boat* boat){
  free(boat -> ship);
  free(boat);
}

/**
* Function name : destroyBoat()
* Usage         : destroyBoat(Boat*);
* Definition    : This function deallocs everything.
*/

void destroyBoat(Boat* boat){
  destroyCoords(boat -> coords);
  destroyTempBoat(boat);
}

/**
* Function name : setShip()
* Usage         : setShip(Boat*,int,int,int);
* Definition    : This function updates the boat structure when it suffers an attack.
*/

void setShip(Boat* boat, int value, int x, int y){
  if(value >= 0 && value <= 3){
    if(boat -> id == 'l') {
      boat -> ship[(x - boat -> coords -> row)*BITMAP_SIZE + y - boat -> coords -> column] = value;
    }
    else {
      switch(boat -> coords -> rotation){
        case 0  : boat -> ship[(x - boat -> coords -> row + 2)*BITMAP_SIZE + y - boat -> coords -> column] = value; break;
        case 90 : boat -> ship[(BITMAP_SIZE - 1 - (x - boat -> coords -> row))*BITMAP_SIZE + y - boat -> coords -> column + 2] = value; break;
        case 180: boat -> ship[(x - boat -> coords -> row + 2)*BITMAP_SIZE + BITMAP_SIZE - 1 - (y - boat -> coords -> column)] = value; break;
        case 270: boat -> ship[(x - boat -> coords -> row)*BITMAP_SIZE + y - boat -> coords -> column + 2] = value; break;
      }
    }
  }
}
