#include <stdlib.h>
#include <stdbool.h>
#include "global_var.h"

QD_Node* buildNode(QD_TNODE type){
	QD_Node new = (QD_Node *)malloc(sizeof(QD_Node));
	new.type = type;

}

void removeNode(QD_Node* node){
	if(node.type == QDLEAF){
		free(node);
	}
}

void insertNode(QD_Node* node, Point p){

}

indexQuad quadrants(Point p,Point corners, int side) {
	int x = corners.x + side/2, y =  corners.y - side/2;
	if(p.x < x){
		if(p.y < y){
			return NW;
		}
		return SE;
	}
	else{
		if(p.y < y){
			return NE;
		}
		return SW;
		}
	}
}

QD_Node* startSearch(QD_Node* root, Point p){
	search(root,p,n_matrix);
}

QD_Node* search(QD_Node* node, Point p, Point sw, int side){

	if(node == null) {
		return null;
	}

	if(node.type == QDLEAF)){
		if(isEqual(node.leaf.p, p)){
				return node;
		}
		else{
			return null;
		}
	}

	indexQuad index = quadrants(p,sw,side);
	int middleSide = side/2;
	switch(index){
		case SW:
			return search(node->quadrants[0],p,sw, middleSide);
		case NW:
			return search(node->quadrants[1],p, makePoint(sw.x,sw.y - middleSide), middleSide);
		case NE:
			return search(node->quadrants[2],p, makePoint(sw.x + middleSide, sw.y - middleSide), middleSide);
		case SE:
			return search(node->quadrants[3],p, makePoint(sw.x + middleSide, sw.y),middleSide);
	}
	return exit(1);
}
