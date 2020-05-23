#include <stdlib.h>
#include <stdbool.h>
#include "global_var.h"

QD_Node* buildNode(QD_TNODE type){
	QD_Node new = (QD_Node *)malloc(sizeof(QD_Node));
	new.type = type;

}

void destroyNode(QD_Node* node){
	if(node.type == QDLEAF){
		free(node);
	}
}

indexQuad quadrants(Point p,Point corners, int side) {
	int middleX = corners.x + side/2, middleY =  corners.y - side/2;
	if(p.x < middleX){
		if(p.y < middleY){
			return NW;
		}
		return SE;
	}
	else{
		if(p.y < middleY){
			return NE;
		}
		return SW;
		}
	}
}

void removeNode(QD_Node* root, Point destiny){
	if(root == null){
		return;
	}

	if(root.type == QDLEAF && isEqual(root.p,destiny)){
		destroyNode(root);
	}

	removeNodeRecursive(root,destiny,makePoint(0,n_matrix),n_matrix);
}

void removeNodeRecursive(QD_Node* node, Point destiny, Point sw, int side){
	indexQuad index = quadrants(destiny,sw,side);
	if(node->quadrants[index] == null){
		return;
	}

	if(isEqual(node->quadrants[index].p, destiny)){
		int sum = 0;
		destroyNode(node->quadrants[index]);
		node->quadrants[index] = null;
		QD_Node* aux = null;
		for(int i = 0; i < nQuadrants; i++){
			if(node->quadrants[i] != null){
				sum++;
				aux = node->quadrants[i];
			}
		}
		if(sum == 1){
			destroyNode(node);
			node = aux;
		}
	}

	index = quadrants(destiny,sw,side);
	int middleSide = side/2;
	switch(index){
		case SW:
			return removeNodeRecursive(node->quadrants[SW],destiny,sw, middleSide);
		case NW:
			return removeNodeRecursive(node->quadrants[NW],destiny, makePoint(sw.x,sw.y - middleSide), middleSide);
		case NE:
			return removeNodeRecursive(node->quadrants[NE],destiny,makePoint(sw.x + middleSide, sw.y - middleSide), middleSide);
		case SE:
			return removeNodeRecursive(node->quadrants[SE],destiny,makePoint(sw.x + middleSide, sw.y),middleSide);
	}
}

void insertNode(QD_Node* root, QD_Node* node, Point destiny,Point sw, int side){

	if(root == null){
		root = node;
		return;
	}

	if(root.type == QDLEAF){
		QD_Node* aux = buildNode(QDNODE);
		indexQuad index = quadrants(root.p,sw,side);
		aux->quadrants[index] = root;
		index = quadrants(node.p,sw,side);
		aux->quadrants[index] = node;
		return;
	}

	//Caso recursivo
	indexQuad index = quadrants(destiny,sw,side);
	int middleSide = side/2;
	switch(index){
		case SW:
			return insertNode(node->quadrants[SW],node,destiny,sw, middleSide);
		case NW:
			return insertNode(node->quadrants[NW],node,destiny,makePoint(sw.x,sw.y - middleSide), middleSide);
		case NE:
			return insertNode(node->quadrants[NE],node,destiny,makePoint(sw.x + middleSide, sw.y - middleSide), middleSide);
		case SE:
			return insertNode(node->quadrants[SE],node,destiny,makePoint(sw.x + middleSide, sw.y),middleSide);
	}
}

QD_Node* startSearch(QD_Node* root, Point p){
	search(root,p,makePoint(0,n_matrix),n_matrix);
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
			return search(node->quadrants[SW],p,sw, middleSide);
		case NW:
			return search(node->quadrants[NW],p, makePoint(sw.x,sw.y - middleSide), middleSide);
		case NE:
			return search(node->quadrants[NE],p, makePoint(sw.x + middleSide, sw.y - middleSide), middleSide);
		case SE:
			return search(node->quadrants[SE],p, makePoint(sw.x + middleSide, sw.y),middleSide);
	}
	return exit(1);
}
