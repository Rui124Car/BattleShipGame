#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef QTREE
#include "game.h"
#else
#include "SeaBattle.h"
#endif


int main(){
	int size = 0;
	int ship_number[5] = {1,1,1,1,1};

	//o uso da flag é útil para verificar se os mallocs estão a dar ou não NULL
	int flag = -1;


	//perguntar ao user o tamanho do tabuleiro
	while(flag != 1){
		printf("Insira o tamanho do tabuleiro\n");
		scanf("%d", &size);

		if (size < 20 || size > 40){
			printf("Esse tamanho não é permitido...\n");
			continue;
		}
		flag = 1;
	}

	printf("Tipos dos barcos:\nTipo 0: Quadrado 1x1;\nTipo 1: Retângulo 1x2;\nTipo 2: Retângulo 1x3;\nTipo 3: Retângulo 1x4;\nTipo 4: Em forma de L.\n");
	printf("\n");

	while(flag != 0){
		flag = ship_number_scan(ship_number, size);
	}	

	int ship_count = array_sum(ship_number); 
	
	int game_mode = 0;
	printf("Prima 0 para colocar aleatoriamente os navios ou outra tecla para colocar manualmente\n");
	scanf("%d", &game_mode);

	Game* P1 = new_game(size, ship_count);
	Game* P2 = new_game(size, ship_count);

	if(P1 == NULL || P2 == NULL){
		printf("A parar. Ocorreu um erro!\n");
		return 1;
	}

	//criação dos barcos do jogo
	flag = 0;

	//criam-se 2 arrays de navios, um para cada jogador, pois as suas configurações serão diferentes
	Ship* game_ship1 = create_ships(ship_number);
	Ship* game_ship2 = create_ships(ship_number);

	if(game_ship1 == NULL || game_ship2 == NULL){
		printf("A parar. Ocorreu um erro!\n");
		return 1;
	}

	//colocação dos barcos
	if(game_mode != 0){
		printf("Jogador 1, insere os teus barcos!\n");
	}

	srand(time(NULL));


	space_check_boat_placement(game_mode, ship_number, P1, game_ship1); //colocação dos barcos do jogador 1


	if(game_mode != 0){
		printf("Jogador 2, insere os teus barcos!\n");	
	}

	space_check_boat_placement(game_mode, ship_number, P2, game_ship2); //colocação dos barcos do jogador 2

	play(P1, P2);

	memory_free(P1, P2, game_ship1, game_ship2);

	return 0;
}
