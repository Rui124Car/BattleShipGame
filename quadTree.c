#include "quadTree.h"

//passamos o canto do setor e o lado completo...
int quadrant_checker(Point p, Point c, int side){


	int xm = c.x + side/2;
	int ym = c.y + side/2;

	if(p.x >= xm){
		if(p.y >= ym)
			return NE;
		else 
			return SE;
	}

	else {
		if(p.y < ym)
			return SW;
		else 
			return NW;
	}
}

//criar um nó folha, que vai corresponder a um ponto do plano
QD_NODE *create_leaf(Point p, Cell *pos){

	QD_NODE *new_node = (QD_NODE*) malloc(sizeof(QD_NODE));
	new_node->node.leaf.pos = pos;

	new_node->node.leaf.p.x = p.x;
	new_node->node.leaf.p.y = p.y;

	new_node->type = QDLEAF;

	return new_node;
}

//calcular o canto SW
Point calculate_sw(Point sw_corner, int side, Point multiplier[], int quadrant){
	if(side == 1){
		return sw_corner;
	}

	Point p = make_point(0,0);

	if(quadrant == SW)
		return sw_corner;

	else if(quadrant == SE)
		p = mult(side/2, multiplier[0]);

	else if(quadrant == NW)
		p = mult(side/2, multiplier[1]);

	else if(quadrant == NE)
		p = mult(side/2, multiplier[2]);


	Point to_return = sum_point(sw_corner, p);
	return to_return;
}



//procurar uma posição na àrvore
QD_NODE *QD_SEARCH(QD_NODE *qtree, Point p, int side, Point sw, Point multiplier[]){

	if(qtree == NULL){
		return qtree;
	}

	if(qtree->type == QDNODE){
		int q = quadrant_checker(p, sw, side);
	
		sw = calculate_sw(sw, side, multiplier, q);

		return QD_SEARCH(qtree->node.quadrants[q], p, side/2, sw, multiplier);
	}

	else{
		int comp = point_compare(qtree->node.leaf.p, p);
		if(comp == 1)
			return qtree;
	}

	return NULL;
}




QD_NODE *QD_INSERT(QD_NODE *qtree, Point p, Cell *pos, Point sw, int side, Point multiplier[]);


void insert_in_node(QD_NODE *qtree, Point p, Cell *pos, Point sw, int side, Point multiplier[]){
	int q = quadrant_checker(p, sw, side);

	if(side <= 1){
		sw.x = p.x;
		sw.y = p.y;
	}

	else 
		sw = calculate_sw(sw, side, multiplier, q);

	qtree->node.quadrants[q] = QD_INSERT(qtree->node.quadrants[q], p, pos, sw, side/2, multiplier);
}

void insert_quadrants(QD_NODE *qtree, Point p, Cell *pos, Point sw, int side, Point multiplier[]){
	Cell *val = qtree->node.leaf.pos;
	Point pval;
	pval.x = qtree->node.leaf.p.x;
	pval.y = qtree->node.leaf.p.y;

	qtree->type = QDNODE;

	for(int i = 0; i<4; i++){
		qtree->node.quadrants[i] = NULL;
	}

	insert_in_node(qtree, pval, val, sw, side, multiplier);

	qtree = QD_INSERT(qtree, p, pos, sw, side, multiplier);
}


QD_NODE *QD_INSERT(QD_NODE *qtree, Point p, Cell *pos, Point sw, int side, Point multiplier[]){
	if(side == 0)
		return create_leaf(p, pos);

	if(qtree == NULL){
		return create_leaf(p, pos);
	}

	else if(qtree->type == QDNODE)
		insert_in_node(qtree, p, pos, sw, side, multiplier);
	else{
		insert_quadrants(qtree, p, pos, sw, side, multiplier);
	}

	return qtree;
}


void free_tree(QD_NODE *qtree){
    if (qtree == NULL) 
        return;

    if(qtree->type == QDNODE){
	    for (int i = 0; i < 4; ++i) {
	        free_tree(qtree->node.quadrants[i]);
	    }
	}
	else{
	    free(qtree);
	}
} 


