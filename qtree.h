#ifndef QTREE
#define QTREE

#define nQuadrants 4

typedef struct {
	char shot;
	char state;
	Boat *ship;
} Cell;

typedef enum { QDNODE, QDLEAF} QD_TNODE;

typedef enum { SW, NW, NE, SE} indexQuad;

typedef struct QD_Node_ {
  QD_TNODE  type;    // defines the type of node (internal node or leaf)

  union {
    struct QD_Node_ *quadrants[nQuadrants];    // internal node
    struct {

      Cell* cell;   // VALUE --  board cell ou pointer para board cell?
      Point p;    // coords of the board cell

    } leaf;     //  almost a board cell together with its coordinates

  } node;

} QD_Node;

QD_Node* buildNode();
//leaf* removeNode();

#endif
