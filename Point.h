#ifndef POINT_H
#define POINT_H
#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int x;
	int y;
}Point;


Point make_point(int x1, int y1); //criar um novo ponto
Point sum_point(Point p1, Point p2); //somar dois pontos
Point mult_point(Point p1, Point p2); //multiplicar dois pontos
Point mult(int side, Point p); //multiplicar um ponto por um inteiro
int is_equal(Point p1, Point p2); //verificar se 2 pontos sao iguais
void print_point(Point p); //printar 1 ponto
Point copy_point(Point origem); //copiar um ponto
int point_compare(Point a, Point b); //comparar 2 pontos


#endif
