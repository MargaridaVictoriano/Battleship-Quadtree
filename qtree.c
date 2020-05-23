#include <stdlib.h>
#include <stdbool.h>

#include "global_var.h"
#include "coords.h"
#include "boat.h"
#include "qtree.h"

QD_Node* buildNode(QD_TNODE type){
	QD_Node* new = (QD_Node *)malloc(sizeof(QD_Node));
	if(new == NULL) exit(-1);
	new->type = type;
	return new;
}

void destroyNode(QD_Node* node){
	free(node);
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

void insertNode(QD_Node* root, QD_Node* node){
	insertNodeRecursive(root, node, makePoint(0,n_matrix), n_matrix);
	return;
}

void insertNodeRecursive(QD_Node* root, QD_Node* node, Point sw, int side){
	
	if(root == NULL){
		root = node;
		return;
	}

	if(root->type == QDLEAF){
		QD_Node* aux = buildNode(QDNODE);
		indexQuad index = quadrants(root->node.leaf.p,sw,side);
		aux->node.quadrants[index] = root;
		index = quadrants(node->node.leaf.p,sw,side);
		aux->node.quadrants[index] = node;
		return;
	}

	//Caso recursivo
	indexQuad index = quadrants(node -> node.leaf.p,sw,side);
	int middleSide = side/2;
	switch(index){
		case SW:
			insertNodeRecursive(node->node.quadrants[SW],node,sw, middleSide);
			return;
		case NW:
			insertNodeRecursive(node->node.quadrants[NW],node,makePoint(sw.x,sw.y - middleSide), middleSide);
			return;
		case NE:
			insertNodeRecursive(node->node.quadrants[NE],node,makePoint(sw.x + middleSide, sw.y - middleSide), middleSide);
			return;
		case SE:
			insertNodeRecursive(node->node.quadrants[SE],node,makePoint(sw.x + middleSide, sw.y),middleSide);
			return;
	}
}

QD_Node* searchNode(QD_Node* root, Point p){
	return searchNodeRecursive(root,p,makePoint(0,n_matrix),n_matrix);
}

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
	int middleSide = side/2;
	switch(index){
		case SW:
			return searchNodeRecursive(node->node.quadrants[SW],p,sw, middleSide);
		case NW:
			return searchNodeRecursive(node->node.quadrants[NW],p, makePoint(sw.x,sw.y - middleSide), middleSide);
		case NE:
			return searchNodeRecursive(node->node.quadrants[NE],p, makePoint(sw.x + middleSide, sw.y - middleSide), middleSide);
		case SE:
			return searchNodeRecursive(node->node.quadrants[SE],p, makePoint(sw.x + middleSide, sw.y),middleSide);
		default: exit(1);
	}
}

void removeNode(QD_Node* root, Point destiny){
	if(root == NULL){
		return;
	}

	if(root->type == QDLEAF && isEqual(root->node.leaf.p,destiny)){
		destroyNode(root);
	}

	removeNodeRecursive(root,destiny,makePoint(0,n_matrix),n_matrix);
}

void removeNodeRecursive(QD_Node* node, Point destiny, Point sw, int side){
	indexQuad index = quadrants(destiny,sw,side);
	if(node->node.quadrants[index] == NULL){
		return;
	}

	if(isEqual(node->node.quadrants[index]->node.leaf.p, destiny)){
		int sum = 0;
		destroyNode(node->node.quadrants[index]);
		node->node.quadrants[index] = NULL;
		QD_Node* aux = NULL;
		for(int i = 0; i < nQuadrants; i++){
			if(node->node.quadrants[i] != NULL){
				sum++;
				aux = node->node.quadrants[i];
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
			removeNodeRecursive(node->node.quadrants[SW],destiny,sw, middleSide);
			return;
		case NW:
			removeNodeRecursive(node->node.quadrants[NW],destiny, makePoint(sw.x,sw.y - middleSide), middleSide);
			return;
		case NE:
			removeNodeRecursive(node->node.quadrants[NE],destiny,makePoint(sw.x + middleSide, sw.y - middleSide), middleSide);
			return;
		case SE:
			removeNodeRecursive(node->node.quadrants[SE],destiny,makePoint(sw.x + middleSide, sw.y),middleSide);
			return;
	}
}
