#ifndef SEABATTLE_H
#define SEABATTLE_H

//API estrutura de dados do jogo
typedef struct{
  char bitmap[5][5]; //bitmap que guarda a figura
  int x; //Para ajudar no mapeamento da figura no bitmap
  int y; //Para ajudar no mapeamento da figura no bitmap
  int rot; //rotação a que o navio foi sujeito
  int tipo; //tipo do navio
  int ship_health; //vida atual do navio
}Ship;

typedef struct{
  int shoot; //Variável que guarda a situação da coordenada (x,y) do adversário
  Ship* pointer_ship;	//apontador para o navio
}Cell;

typedef struct {
  Cell** board; //tabuleiro do jogo
  int b_size; //tamanho do tabuleiro
  int ship_count; //quantidade de navios
}Game;


int  ship_number_scan(int*, int); //leitura dos navios
int  array_sum(int*); //soma de arrays
Game* new_game(int, int); //criar tabuleiro
Ship* create_ships(int*); //alocação dos barcos na memória
int check1(int, int, int); //vê coordenadas gerados pelos aleatórios
void space_check_boat_placement(int, int*, Game*, Ship*); //verificação de espaços e colocação dos barcos
int limit_checker(int, int, int, int, int); //ver se as coordenadas inseridas estão dentro do tabuleiro
int checker(Game*, int, int, int, int); //verificar colisões aquando a inserção
void place_boat(Game*, Ship*, int, int, int, int); //colocação dos barcos
int choose(int); //escolher o angulo de rotação de acordo com o aleatório gerado


void play(Game*, Game*); //funçaõ de processamento de jogo em si
void moving_x_y(Game*, int, int); //mover as variáveis X e Y quando há um hit num navio
void print_state(Game*, Game*); //imprimir o estado atual do jogo
char* validate_coord(int, int, int); //validar uma coordenada quando um jogador a pretende atacar

void memory_free(Game*, Game*, Ship*, Ship*); //libertar a memória alocada

#endif
