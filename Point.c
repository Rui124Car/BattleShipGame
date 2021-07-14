#include <stdlib.h>
#include <stdio.h>

#include "Point.h"


//contrutor 
Point make_point(int x1, int y1){
	Point p;

	p.x = x1;
	p.y = y1;

	return p;
}

//somar 2 pontos
Point sum_point(Point p1, Point p2){

	p1.x = (p1.x + p2.x);
	p1.y = (p1.y + p2.y);

	return p1;
}

//multiplicar 2 pontos
Point mult_point(Point p1, Point p2){
	int x = (p1.x * p2.x);
	int y = (p1.y * p2.y);
	Point q;
	q.x = x;
	q.y=y;

	return q;
}

//multiplica um ponto por um inteiro
Point mult(int side, Point p){
	int x = (p.x * side);
	int y = (p.y * side);
	Point a;
	a.x=x;
	a.y=y;

	return a;
}

//ver se 2 pontos sao iguais
int is_equal(Point p1, Point p2){

	if((p1.x != p2.x) || (p1.y != p2.y))
		return -1;

	return 1;
}


void print_point(Point p){
	printf("(%d;%d)\n", p.x, p.y);
}


Point copy_point(Point origem){
	Point q = make_point(origem.x, origem.y);
	return q;
}


int point_compare(Point a, Point b){
	if(a.x == b.x && a.y == b.y)
		return 1;

	return -1;
}

