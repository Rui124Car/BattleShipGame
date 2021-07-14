#ifndef QUADTREE_H
#define QUADTREE_H
#include "Point.h"

#define SW 0
#define SE 1
#define NW 2
#define NE 3

//estrutura para cada barco
typedef struct{
  char bitmap[5][5]; //bitmap que guarda a figura
  int x; //Para ajudar no mapeamento da figura no bitmap
  int y; //Para ajudar no mapeamento da figura no bitmap
  int rot; //rotação a que o navio foi sujeito
  int tipo; //tipo do navio
  int ship_health; //vida atual do navio
}Ship;

//estrutura para cada posição 
typedef struct{
  int shoot; //Variável que guarda a situação da coordenada (x,y) do adversário
  Ship* pointer_ship;	//apontador para o navio
}Cell;

//estrutura da quadTree
typedef enum { 
	QDNODE, QDLEAF
}QD_TNODE;

typedef struct QD_Node_ {
  QD_TNODE  type;    // defines the type of node (internal node or leaf)
                                       
  union {

    struct QD_Node_ *quadrants[4];    // internal nodes                                                   

    struct {

      Cell *pos;                               
      Point p;    // coords of the board cell  

    } leaf; //almost a board cell together with its coordinates
        
  } node;

}QD_NODE;

//estrutura do jogo
typedef struct {
  QD_NODE *board; //árvore que vai representar o tabuleiro de jogo
  int b_size; //tamanho do tabuleiro
  int ship_number; //quantidade de barcos 
}Game;



int quadrant_checker(Point, Point, int); //quadrante de um ponto
QD_NODE *create_leaf(Point, Cell*); //criar um nó folha, que vai corresponder a um ponto do plano
Point calculate_sw(Point, int, Point[], int); //calcular o canto SW
QD_NODE *QD_SEARCH(QD_NODE*, Point, int, Point, Point[]); //procurar uma posição na àrvore
QD_NODE *QD_INSERT(QD_NODE*, Point, Cell*, Point, int, Point[]); //inserir um ponto
void insert_in_node(QD_NODE*, Point, Cell*, Point, int, Point[]); //inserir num nó
void insert_quadrants(QD_NODE*, Point, Cell*, Point, int, Point[]); //inserir num quadrante
void free_tree(QD_NODE*); //detruir a árvore


#endif
