#ifndef BOAT
#define BOAT

#define BITMAP_SIZE 5

#include "coords.h"

typedef struct {
	char id;
	Coords* coords;
	unsigned char hp;
	char *ship;
} Boat;

extern const char listBoat[];
extern const char l[];
extern const char c[];
extern const char b[];
extern const char r[];
extern const char s[];
extern const char d[];

signed char indexBoat(char);
signed char boatSize(char);
const char* boatName(char);
void boatRot(Boat*);
void prepareBoat(Boat*);
Boat* buildBoat(char,Coords*);
void destroyTempBoat(Boat*);
void destroyBoat(Boat*);
void setShip(Boat*,int,int,int);

#endif
