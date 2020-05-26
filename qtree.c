#include <stdlib.h>
#include <stdbool.h>

#include "global_var.h"
#include "coords.h"
#include "boat.h"
#include "qtree.h"

//#include <stdio.h>

const int canonicalCoords[4][2] = {{0,0},{0,1},{1,1},{1,0}};

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

QD_Node* insertNode(QD_Node* root, QD_Node* node){
	return insertNodeRecursive(root, node, makePoint(0,0), width);
}

QD_Node* insertNodeRecursive(QD_Node* root, QD_Node* node, Point sw, int side){
	
	if(root == NULL){
		//printf("inseri num no null, node (%d,%d)\n\n",node -> node.leaf.p.x,node -> node.leaf.p.y);
		root = node;
		return root;
	}

	if(root->type == QDLEAF){
		//printf("fiz split para uma nova arvore\n");
		
		QD_Node* aux = buildNode(QDLEAF);
		aux -> node.leaf.p = root -> node.leaf.p;
		aux -> node.leaf.cell = root -> node.leaf.cell;
		
		root -> type = QDNODE;
		for(int i = 0; i < nQuadrants ; i++){
			root -> node.quadrants[i] = NULL;
		}
		
		//printf("(%d,%d), side = %d\n",sw.x,sw.y,side);
		indexQuad index = quadrants(aux -> node.leaf.p,sw,side);
		root -> node.quadrants[index] = insertNextNode(root,aux,sw,side,index);
		
	}

	//Caso recursivo
	indexQuad index = quadrants(node -> node.leaf.p,sw,side);
	//printf("(%d,%d), side = %d\n",sw.x,sw.y,side);
	root -> node.quadrants[index] = insertNextNode(root,node,sw,side,index);
	
	return root;
}

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

QD_Node* searchNode(QD_Node* root, Point p){
	return searchNodeRecursive(root,p,makePoint(0,0),width);
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
	return searchNextNode(node, p, sw, side, index);
}

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

void destroyQTree(QD_Node* root){
	destroyQTreeRecursive(root,makePoint(0,0),width);
	return;
}

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

/*void removeNode(QD_Node* root, Point destiny){
	if(root == NULL){
		return;
	}

	if(root->type == QDLEAF){
		if(isEqual(root->node.leaf.p,destiny)){
			destroyNode(root);
		}
		return;
	}

	removeNodeRecursive(root,destiny,makePoint(0,0),width);
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
			removeNodeRecursive(node->node.quadrants[NW],destiny, makePoint(sw.x,sw.y + middleSide), middleSide);
			return;
		case NE:
			removeNodeRecursive(node->node.quadrants[NE],destiny,makePoint(sw.x + middleSide, sw.y + middleSide), middleSide);
			return;
		case SE:
			removeNodeRecursive(node->node.quadrants[SE],destiny,makePoint(sw.x + middleSide, sw.y),middleSide);
			return;
	}
}*/
