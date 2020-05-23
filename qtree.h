#ifndef QTREE
#define QTREE

#define nQuadrants 4

#include "cell.h"
#include "point.h"

typedef enum { QDNODE, QDLEAF} QD_TNODE;

typedef enum { SW = 0, NW = 1, NE = 2, SE = 3} indexQuad;

typedef struct QD_Node_ {
  QD_TNODE  type;    // defines the type of node (internal node or leaf)

  union {
    struct QD_Node_ *quadrants[nQuadrants];    // internal node
    struct {

      Cell cell;  // VALUE --  board cell
      Point p;    // coords of the board cell

    } leaf;     //  almost a board cell together with its coordinates

  } node;

} QD_Node;

QD_Node* buildNode(QD_TNODE);
void destroyNode(QD_Node*);
indexQuad quadrants(Point,Point, int);
void insertNode(QD_Node*,QD_Node*);
void insertNodeRecursive(QD_Node*,QD_Node*,Point,int);
QD_Node* searchNode(QD_Node*,Point);
QD_Node* searchNodeRecursive(QD_Node*,Point,Point,int);
void removeNode(QD_Node*,Point);
void removeNodeRecursive(QD_Node*,Point,Point,int);

#endif
