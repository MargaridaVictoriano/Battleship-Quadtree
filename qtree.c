#include <stdlib.h>
#include <stdbool.h>

#include "global_var.h"
#include "coords.h"
#include "boat.h"
#include "qtree.h"

const int canonicalCoords[4][2] = {{0,0},{0,1},{1,1},{1,0}};

/**
* Funtion name : buildNode()
* Usage				 : buildNode(QD_TNODE)
* Definition   : This function builds and returns a new node.
*/
QD_Node* buildNode(QD_TNODE type){
	QD_Node* new = (QD_Node *)malloc(sizeof(QD_Node));
	if(new == NULL) exit(-1);
	new->type = type;
	return new;
}

/**
* Function name : destroyNode()
* Usage        : destroyNode(QD_Node*)
* Definition   : This function receives a node and frees the memory.
*/
void destroyNode(QD_Node* node){
	free(node);
}

/**
* Function name : quadrants()
* Usage					: quadrants(Point ,Point, int)
* Definition    : This function receives information about a point and returns the corresponding quadrant index.
*/
indexQuad quadrants(Point p,Point corners, int side) {
	int middleX = corners.x + side/2, middleY =  corners.y + side/2;
	if(p.x < middleX){
		if(p.y < middleY){
			return SW;
		}
		return NW;
	}
	else{
		if(p.y < middleY){
			return SE;
		}
		return NE;
	}
}

/**
* Function name : insertNode()
* Usage 				: insertNode(QD_Node*, QD_Node*)
*Definition     : This function receives the root node,a given node and returns the recursive funtion to insert a new node.
*/

QD_Node* insertNode(QD_Node* root, QD_Node* node){
	return insertNodeRecursive(root, node, makePoint(0,0), width);
}

/**
* Function name : insertNodeRecursive()
* Usage         : insertNodeRecursive(QD_Node*, QD_Node*, Point, int)
* Definition    : This function inserts a node recursively.
* 								If the tree is empty, we insert and return the root node.
* 								If the root is a leaf node,
*/
QD_Node* insertNodeRecursive(QD_Node* root, QD_Node* node, Point sw, int side){

	if(root == NULL){
		root = node;
		return root;
	}

	if(root->type == QDLEAF){

		QD_Node* aux = buildNode(QDLEAF);
		aux -> node.leaf.p = root -> node.leaf.p;
		aux -> node.leaf.cell = root -> node.leaf.cell;

		root -> type = QDNODE;
		for(int i = 0; i < nQuadrants ; i++){
			root -> node.quadrants[i] = NULL;
		}

		indexQuad index = quadrants(aux -> node.leaf.p,sw,side);
		root -> node.quadrants[index] = insertNextNode(root,aux,sw,side,index);

	}

	//Recursive Case
	indexQuad index = quadrants(node -> node.leaf.p,sw,side);
	root -> node.quadrants[index] = insertNextNode(root,node,sw,side,index);

	return root;
}

/**
* Function name : insertNextNode()
* Usage         : insertNextNode(QD_Node*, QD_Node*, Point , int, indexQuad)
* Definition    :
*/
QD_Node* insertNextNode(QD_Node* root, QD_Node* node, Point sw, int side, indexQuad index){
	int middleSide = side/2;

	return insertNodeRecursive(
		root -> node.quadrants[index],
		node,
		makePoint(
			sw.x + middleSide * canonicalCoords[index][0],
			sw.y + middleSide * canonicalCoords[index][1]
			),
		middleSide
		);
}

/**
* Function name : searchNode(QD_Node*, Point)
* Usage					: searchNode(QD_Node*, Point)
* Definition    : This functions starts the search from the root node and returns the recursive search funtion.
*/
QD_Node* searchNode(QD_Node* root, Point p){
	return searchNodeRecursive(root,p,makePoint(0,0),width);
}

/**
* Function name : searchNodeRecursive()
* Usage         : searchNodeRecursive(QD_Node*, Point, Point, int)
* Definition    : This function searches the node recursively.
*/

QD_Node* searchNodeRecursive(QD_Node* node, Point p, Point sw, int side){

	if(node == NULL) {
		return NULL;
	}

	if(node->type == QDLEAF){
		if(isEqual(node->node.leaf.p, p)){
			return node;
		}
		else{
			return NULL;
		}
	}

	indexQuad index = quadrants(p,sw,side);
	return searchNextNode(node, p, sw, side, index);
}

/**
** Function name : searchNextNode()
* Usage          : searchNextNode(QD_Node*, Point, Point , int, indexQuad)
* Definition     :
*/
QD_Node* searchNextNode(QD_Node* root, Point p, Point sw, int side, indexQuad index){
	int middleSide = side/2;

	return searchNodeRecursive(
		root -> node.quadrants[index],
		p,
		makePoint(
			sw.x + middleSide * canonicalCoords[index][0],
			sw.y + middleSide * canonicalCoords[index][1]
			),
		middleSide
		);
}
/**
* Function name : destroyQTree()
* Usage         : destroyQTree(QD_Node*)
* Definition    : This functions receives the root node and calls the recursive funtion to start the destroying process.
*/
void destroyQTree(QD_Node* root){
	destroyQTreeRecursive(root,makePoint(0,0),width);
	return;
}

/**
* Function name : destroyQTreeRecursive()
* Usage         : destroyQTreeRecursive(QD_Node*, Point, int)
* Definition    : This function destroys the tree recursively.
*/
void destroyQTreeRecursive(QD_Node* node, Point sw, int side){
	if(node == NULL) {
		return;
	}

	if(node->type == QDLEAF){
		destroyNode(node);
		return;
	}

	int middleSide = side/2;
	for(int i = 0; i < nQuadrants ; i++){
		destroyQTreeRecursive(
			node -> node.quadrants[i],
			makePoint(
				sw.x + middleSide * canonicalCoords[i][0],
				sw.y + middleSide * canonicalCoords[i][1]
				),
			middleSide
			);
	}

	destroyNode(node);
	return;
}
