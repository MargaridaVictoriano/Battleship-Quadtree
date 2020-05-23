#include <stdbool.h>
#include "point.h"

Point makePoint(int x, int y){
  Point p;
  p.x = x;
  p.y = y;
  return p;
}

Point addPoint(Point p, Point q){
  Point sum;
  sum.x = p.x + q.x;
  sum.y = p.y + q.y;
  return sum;
}

bool isEqual(Point p, Point q){
  if(p.x == q.x && p.y == q.y){
    return true;
  }
  return false;
}

//Assumindo que o corner é o canto inferior esquerdo
bool inSquare(Point p, Point corner, int side){
  if(p.x >= corner.x && p.x < corner.x + side && p.y >= corner.y - side && p.y < corner.y){
    return true;
  }
  return false;
}
