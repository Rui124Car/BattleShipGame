#ifndef GAME_H
#define GAME_H 
#include "quadTree.h"

//API estrutura de dados do jogo
int  ship_number_scan(int*, int); //leitura dos navios
int  array_sum(int*); //soma de arrays
Game* new_game(int, int); //criar tabuleiro
Ship* create_ships(int*); //alocação dos barcos na memória
int check1(int, int, int); //verifica os posições, tendo em conta o tamanho do tabuleiro
int pos_checker(int, int, QD_NODE*); //auxiliar de checker
int checker(QD_NODE*, Point, int, int);//verifica o tabuleiro por possiveis colisões
int choose(int); //escolhe o angulo de rotação na colocação aleatória
QD_NODE *place_boat(Game*, Ship*, int, int, int, int); //coloca os barcos
Cell *create_cell(Ship*, int); //cria uma variável do tipo Cell* e retorna
void space_check_boat_placement(int, int*, Game*, Ship*); //verifica os espaços a ocupar e coloca os barcos
void moving_x_y(Game*, int, int); //mover o x e y do ship quando há 1 hit
char* validate_coord(int, int, int); //validar coordenadas de ataque
void print_state(Game*, Game*); //print dos tabuleiros
void play(Game*, Game*); //receção das coordenadas de ataque e processamento das mesmas
void memory_free(Game*, Game*, Ship*, Ship*); //libertar memória
#endif
