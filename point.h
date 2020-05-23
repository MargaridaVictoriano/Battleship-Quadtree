#ifndef POINT
#define POINT

typedef struct {
	int x,y;
} Point;

Point makePoint(int, int);
Point addPoint(Point, Point);
bool isEqual(Point, Point);
bool inSquare(Point, Point, int);

#endif
