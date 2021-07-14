#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SeaBattle.h"

//leitura da quantidade de navios de cada tipo
int ship_number_scan(int* ship_number, int size){
  int control = 0;
  int temp = (size*size) / (5*5);

  printf("A quantidade máxima de barcos é de %d\n", temp);
  printf("Se a quantidade inserida for 0, será colocado 1 barco desse tipo.\n");
  printf("\n");

  for(int i = 0; i<5; i++){
    printf("Insere a quantidade de barcos do tipo %d\n", i);
    scanf("%d", &ship_number[i]);
    printf("\n");

    if (ship_number[i] == 0){
      ship_number[i] = 1;
    }
  
    control += ship_number[i];

    if(control > temp){
      printf("Já colocas-te barcos a mais...\n");
      return 1;
    }
  }
  return 0;
}

//soma dos valores num array
int array_sum(int *arr){
	int var = 0;
	for(int i = 0; i<5; i++){
		for(int j = 0; j<5; j++){
			var += arr[i];
		}
	}

	return var;
}

//criação de um tabuleiro de jogo
Game* new_game(int b_size, int ship_count){
  Game* g = (Game*) malloc(sizeof(Game));
  if(g == NULL)
   return NULL;

  //inicialização do tabuleiro
  g->board = (Cell**) malloc(b_size * sizeof(Cell*));
  if(g->board == NULL)
  	return NULL;

  g->b_size = b_size;
 
  for(int i = 0; i<b_size; i++){
	    g->board[i] = (Cell*) malloc(b_size * sizeof(Cell));

	    if(g->board[i] == NULL){
	    	return NULL;
	    }
  	} 

  g->ship_count = ship_count;	

  for(int i = 0; i<b_size; i++){
    for(int j = 0; j<b_size; j++){  
      g->board[i][j].shoot = 0;
      g->board[i][j].pointer_ship = 0;
  	}
  }
  
  return g;
}

//criação dos navios de jogo
Ship* create_ships(int* ship_number){
	//contar o numero total de navios
	int total_ships = 0;
	for(int i = 0; i<5; i++){
		total_ships += ship_number[i];
	}

	//alocar o espaço para guardar todos os navios necessários
	Ship* game_ship = (Ship*) malloc(total_ships * sizeof(Ship));
	if(game_ship == NULL)
		return NULL;


	for(int i = 0; i<5; i++){
		for(int j = 0; j<ship_number[i]; j++){
			//as variaveis x e y servem para fazer mais facilmente o mapeamento da peça no bitmap
			//desenhar os barcos no bitmap
			//faz-se switch no i porque ele define o tipo de barco
			switch(i){
				//quadrado 1x1
				case 0:{
					for(int k = 0; k<5; k++){
						for(int l = 0; l<5; l++){
							game_ship[i].bitmap[k][l] = '0';
						}
					}
					game_ship[i].bitmap[2][2] = '1';
					game_ship[i].x = 2;
					game_ship[i].y = 2;
					game_ship[i].tipo = i;
					game_ship[i].ship_health = i+1;
					break;
				}
				//retangulo 1x2
				case 1:{
					for(int k = 0; k<5; k++){
						for(int l = 0; l<5; l++){
							game_ship->bitmap[k][l] = '0';
						}
					}
					game_ship[i].bitmap[2][2] = '1';
					game_ship[i].bitmap[3][2] = '1';
					game_ship[i].x = 2;
					game_ship[i].y = 2;
					game_ship[i].tipo = i;
					game_ship[i].ship_health = i+1;
					break;
				}
				//retangulo 1x3
				case 2:{
					for(int k = 0; k<5; k++){
						for(int l = 0; l<5; l++){
							game_ship->bitmap[k][l] = '0';
						}
					}
					game_ship[i].bitmap[1][2] = '1';
					game_ship[i].bitmap[2][2] = '1';
					game_ship[i].bitmap[3][2] = '1';
					game_ship[i].x = 1;
					game_ship[i].y = 2;
					game_ship[i].tipo = i;
					game_ship[i].ship_health = i+1;
					break;
				}
				//retangulo 1x4
				case 3:{
					for(int k = 0; k<5; k++){
						for(int l = 0; l<5; l++){
							game_ship->bitmap[k][l] = '0';
						}
					}
					game_ship[i].bitmap[1][2] = '1';
					game_ship[i].bitmap[2][2] = '1';
					game_ship[i].bitmap[3][2] = '1';
					game_ship[i].bitmap[4][2] = '1';
					game_ship[i].x = 1;
					game_ship[i].y = 2;
					game_ship[i].tipo = i;
					game_ship[i].ship_health = i+1;
					break;
				}
				//Barco em L
				case 4:{
					for(int k = 0; k<5; k++){
						for(int l = 0; l<5; l++){
							game_ship->bitmap[k][l] = '0';
						}
					}
					game_ship[i].bitmap[1][2] = '1';
					game_ship[i].bitmap[2][2] = '1';
					game_ship[i].bitmap[3][2] = '1';
					game_ship[i].bitmap[3][3] = '1';
					game_ship[i].bitmap[3][4] = '1';
					game_ship[i].x = 1;
					game_ship[i].y = 2;
					game_ship[i].tipo = i;
					game_ship[i].ship_health = i+1;
					break;
				}


				default: break;
			}
		}
	}
	return game_ship;
}

//função para verificar espaços ao inserir os barcos
int checker(Game* g, int tipo, int rot, int x, int y){
	switch(tipo){
		//1x1
		case 0:{

			if(g->board[x][y].pointer_ship == 0)
				return 0;
			break;
		}

		//1x2
		case 1:{
			//rotações de 0 e 360
			if(rot == 0 || rot == 360){
				if((g->board[x][y].pointer_ship == 0) && (g->board[x+1][y].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}

			//rotações de 90
			else if(rot == 90){
				if((g->board[x][y].pointer_ship == 0) && (g->board[x][y+1].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}

			//rotações de 180
			else if(rot == 180){
				if((g->board[x][y].pointer_ship == 0) && (g->board[x-1][y].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}

			//rotações de 270
			else if (rot == 270){

				if((g->board[x][y].pointer_ship == 0) && (g->board[x][y-1].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}
			break;
		}

		//1x3
		/*neste caso juntam-se as rotações de 0 e 180, 90 e 270
		porque o barco é simétrico em relação ao centro da matriz*/
		
		case 2:{
			//rotações de 0, 180 e 360
			if(rot == 0 || rot == 180 || rot == 360){
				if((g->board[x][y].pointer_ship == 0) && (g->board[x+1][y].pointer_ship == 0) && 
					(g->board[x-1][y].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}

			else if(rot == 90 || rot == 270){
				if((g->board[x][y].pointer_ship == 0) && (g->board[x][y+1].pointer_ship == 0) &&
				   (g->board[x][y-1].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}
			break;
		}

		//1x4
		case 3:{
			//rotações de 0 e 360
			if(rot == 0 || rot == 360){
				if((g->board[x][y].pointer_ship == 0) && (g->board[x-1][y].pointer_ship == 0) &&
					(g->board[x+1][y].pointer_ship == 0) && (g->board[x+2][y].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}

			//rotações de 90
			else if(rot == 90){
				if((g->board[x][y].pointer_ship == 0) && (g->board[x][y-1].pointer_ship == 0) &&
			       (g->board[x][y+1].pointer_ship == 0) && (g->board[x][y+2].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}

			//rotações de 180
			else if(rot == 180){
				if((g->board[x][y].pointer_ship == 0) && (g->board[x-2][y].pointer_ship == 0) &&
					(g->board[x-1][y].pointer_ship == 0) && (g->board[x+1][y].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}

			//rotações de 270
			else if (rot == 270){

				if((g->board[x][y].pointer_ship == 0) && (g->board[x][y-2].pointer_ship == 0) &&
				   (g->board[x][y-1].pointer_ship == 0) && (g->board[x][y+1].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}
			break;
		}

		//L
		case 4:{
			//rotações de 0 e 360
			if(rot == 0 || rot == 360){
				if((g->board[x][y].pointer_ship == 0) && (g->board[x-1][y].pointer_ship == 0) &&
					(g->board[x+1][y].pointer_ship == 0) && (g->board[x+1][y+1].pointer_ship == 0) &&
					(g->board[x+1][y+2].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}

			//rotações de 90
			else if(rot == 90){
				if((g->board[x][y].pointer_ship == 0) && (g->board[x][y-1].pointer_ship == 0) &&
				   (g->board[x][y+1].pointer_ship == 0) && (g->board[x-2][y+1].pointer_ship == 0) &&
				   (g->board[x-1][y+1].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}

			//rotações de 180
			else if(rot == 180){
				if((g->board[x][y].pointer_ship == 0) && (g->board[x+1][y].pointer_ship == 0) &&
				   (g->board[x-1][y].pointer_ship == 0) && (g->board[x-1][y-1].pointer_ship == 0) &&
				   (g->board[x-1][y-2].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}

			//rotações de 270
			else if (rot == 270){

				if((g->board[x][y].pointer_ship == 0) && (g->board[x][y-1].pointer_ship == 0) &&
				   (g->board[x][y+1].pointer_ship == 0) && (g->board[x+1][y-1].pointer_ship == 0) && 
				   (g->board[x+2][y-1].pointer_ship == 0))
					return 0;
				else 
					return -1;
			}
			
			break;
		}

		default: return -1;
	}
	return -1;
}

int limit_checker(int size, int tipo, int rot, int x, int y){
	switch(tipo){

		//neste caso a rotação é indiferente
		case 0:{
			if((x < 0) || (y<0) || (x > size) || (y > size))
				return -1;
			else 
				return 0;
			break;
		}

		case 1:{
			if (rot == 0 || rot == 360){
				if ((x < 0) || ((x+1) > size) || (y < 0) || (y > size))
					return -1;
				else 
					return 0;
			}

			else if (rot == 90){
				if((y < 0) || ((y+1) > size) || (x < 0) || (x > size))
					return 1;
				else 
					return 0;
			}

			else if (rot == 180){
				if(((x-1) < 0) || (x > size) || (y < 0) || (y > size))
					return -1;
				else 
					return 0;
			}

			else if (rot == 270){
				if(((y-1) < 0) || (y > size) || (x < 0) || (x > size))
					return -1;
				else 
					return 0;
			}
			break;
		}

		case 2:{
			if (rot == 0 || rot == 360){
				if (((x-1) < 0) || ((x+1) > size) || (y < 0) || (y > size))
					return -1;
				else 
					return 0;
			}

			else if (rot == 90){
				if(((y-1) < 0) || ((y+1) > size) || (x < 0) || (x > size))
					return 1;
				else 
					return 0;
			}

			else if (rot == 180){
				if(((x-1) < 0) || ((x+1) > size) || (y < 0) || (y > size))
					return -1;
				else 
					return 0;
			}

			else if (rot == 270){
				if(((y-1) < 0) || ((y+1) > size) || (x < 0) || (x > size))
					return -1;
				else 
					return 0;
			}
			break;
		}

		case 3:{
			if (rot == 0 || rot == 360){
				if (((x-1) < 0) || ((x+2) > size) || (y < 0) || (y > size))
					return -1;
				else 
					return 0;
			}

			else if (rot == 90){
				if(((y-1) < 0) || ((y+2) > size) || (x < 0) || (x > size))
					return 1;
				else 
					return 0;
			}

			else if (rot == 180){
				if(((x-2) < 0) || ((x+1) > size) || (y < 0) || (y > size))
					return -1;
				else 
					return 0;
			}

			else if (rot == 270){
				if(((y-2) < 0) || ((y+1) > size) || (x < 0) || (x > size))
					return -1;
				else 
					return 0;
			}
			break;
		}

		case 4:{
			if (rot == 0 || rot == 360){
				if (((x-1) < 0) || ((x+1) > size) || (y < 0) || ((y+2) > size))
					return -1;
				else 
					return 0;
			}

			else if (rot == 90){
				if (((y-2) < 0) || ((y+1) > size) || (x > size) || ((x-2) < 0))
					return -1;
				else 
					return 0;
			}

			else if (rot == 180){
				if(((x-1) < 0) || ((x+1) > size) || ((y-2) < 0) || (y > size))
					return -1;
				else 
					return 0;
			}

			else if (rot == 270){
			if(((y-1) < 0) || ((y+1) > size) || ((x+2) > size) || (x < 0))
					return -1;
				else 
					return 0;
			}
			break;
		}
		default: return -1;
	}
	return -1;

}

//inserção no tabuleiro
void place_boat(Game* g, Ship *ship, int rot, int x, int y, int tipo){
	switch(tipo){
		case 0:{
			g->board[x][y].pointer_ship = ship;
			break;
		}

		case 1:{
			//rotações de 0 e 360
			if(rot == 0 || rot == 360){
					g->board[x][y].pointer_ship = ship;
					g->board[x+1][y].pointer_ship = ship;
			}

			//rotações de 90
			else if(rot == 90){
				g->board[x][y].pointer_ship = ship;
				g->board[x][y+1].pointer_ship = ship;
			}

			//rotações de 180
			else if(rot == 180){
				g->board[x][y].pointer_ship = ship;
				g->board[x-1][y].pointer_ship = ship;
				
			}

			//rotações de 270
			else if (rot == 270){

				g->board[x][y].pointer_ship = ship;
				g->board[x][y-1].pointer_ship = ship;
			}
			break;
		}

		//1x3
		
		case 2:{
			//rotações de 0, 180 e 360
			if(rot == 0 || rot == 180 || rot == 360){
				g->board[x][y].pointer_ship = ship;
				g->board[x+1][y].pointer_ship = ship;
				g->board[x-1][y].pointer_ship = ship;
			}

			else if(rot == 90 || rot == 270){
				g->board[x][y].pointer_ship = ship;
				g->board[x][y+1].pointer_ship = ship;
			    g->board[x][y-1].pointer_ship = ship;
			}
			break;
		}

		//1x4
		case 3:{
			//rotações de 0 e 360
			if(rot == 0 || rot == 360){
				g->board[x][y].pointer_ship = ship;
				g->board[x-1][y].pointer_ship = ship;
				g->board[x+1][y].pointer_ship = ship;
				g->board[x+2][y].pointer_ship = ship;
			}

			//rotações de 90
			else if(rot == 90){
				g->board[x][y].pointer_ship = ship;
				g->board[x][y-1].pointer_ship = ship;
			    g->board[x][y+1].pointer_ship = ship;
			   	g->board[x][y+2].pointer_ship = ship;
			}

			//rotações de 180
			else if(rot == 180){
				g->board[x][y].pointer_ship = ship;
				g->board[x-2][y].pointer_ship = ship;
				g->board[x-1][y].pointer_ship = ship;
				g->board[x+1][y].pointer_ship = ship;
			}

			//rotações de 270
			else if (rot == 270){
				g->board[x][y].pointer_ship = ship;
				g->board[x][y-2].pointer_ship = ship;
				g->board[x][y-1].pointer_ship = ship;
				g->board[x][y+1].pointer_ship = ship;
			}
			break;
		}

		//L
		case 4:{
			//rotações de 0 e 360
			if(rot == 0 || rot == 360){
				g->board[x][y].pointer_ship = ship;
				g->board[x-1][y].pointer_ship = ship;
				g->board[x+1][y].pointer_ship = ship;
				g->board[x+1][y+1].pointer_ship = ship;
				g->board[x+1][y+2].pointer_ship = ship;
			}

			//rotações de 90
			else if(rot == 90){
				g->board[x][y].pointer_ship = ship;
				g->board[x][y-1].pointer_ship = ship;
				g->board[x][y+1].pointer_ship = ship;
				g->board[x-1][y+1].pointer_ship = ship;
				g->board[x-2][y+1].pointer_ship = ship;
			}

			//rotações de 180
			else if(rot == 180){
				g->board[x][y].pointer_ship = ship;
				g->board[x+1][y].pointer_ship = ship;
			    g->board[x-1][y].pointer_ship = ship;	   
			    g->board[x-1][y-1].pointer_ship = ship;
			    g->board[x-1][y-2].pointer_ship = ship;
			}

			//rotações de 270
			else if (rot == 270){
				g->board[x][y].pointer_ship = ship;
				g->board[x][y-1].pointer_ship = ship;
			    g->board[x][y+1].pointer_ship = ship;
			    g->board[x+1][y-1].pointer_ship = ship;
		   	    g->board[x+2][y-1].pointer_ship = ship;
			}
			break;
		}
		default: return;
	}
}

int choose(int r){
	switch(r){
		case 0: return 0;
		case 1: return 90;
		case 2: return 180;
		case 3: return 270;
		default: return 0;
	}
	return 0;
}

int check1(int x, int y, int size){
 	if((x > 2) && (x < (size - 2)) && (y > 2) && (y < (size - 2)))
 		return 0;

	return -1;
}

//verificação de espaços e colocação dos navios
void space_check_boat_placement(int game_mode, int ship_number[], Game* g, Ship* game_ship){
	int x = 0;
	int y = 0;
	int flag = 0;
	int rot = 0;

	//colocar os barcos manualmente
	//----------------------------------------------------------------------------------------------------
	if(game_mode != 0){

		/*colocação dos navios em L
		colocamos primeiro os navios em L porque sao os que ocupam mais espaço
		logo, com o tabuleiro vazio, há mais espaço para ocuparem*/

		for(int i = ship_number[4]; i<2*ship_number[4]; i++){
			printf("Estás a inserir um navio do tipo 4 (Forma em L)\n");

			//rotação do navio
			printf("Insere o valor da rotação que pretendes(0, 90, 180, 270 ou 360)\n");
			scanf("%d", &rot);

			if((rot != 0) && (rot != 90) && (rot != 180) && (rot != 270) && (rot != 360)){
				printf("Valor de rotação inválido. Será usada rotação de 0 graus\n");
				rot = 0;
			}

			game_ship[i].rot = rot;

			flag = -1;

			//verificação dos espaços a serem ocupados pelo navio
			//se a coordenada for inválida, o ciclo diz que é invalida e pede novas instruções

			while(flag != 0){
				printf("Insere as coordenadas do navio\n");
				scanf("%d%d", &x, &y);

				//ver se o navio está dentro dos limites do tabuleiro
				flag = limit_checker(g->b_size, 4, rot, x, y);
				if(flag == -1){
					printf("Esse espaço é inválido, tenta outra vez!\n");
					continue;
				}

				//verificar se as posições de colocação não colidem com outro navio
				flag = checker(g, 4, rot, x, y);

				if(flag == -1){
					printf("Esse espaço é inválido, tenta outra vez!\n");
				}
			}

			/*neste ponto, as posições necessárias para inserção
			já foram verificadas*/

			place_boat(g, &game_ship[i], rot, x, y, 4); 
			printf("\n");
		}

		/*inserção dos restantes navio
		fazemos depois porque são mais simples 
		de inserir*/

		for(int i = 0; i<4; i++){
			for(int j = ship_number[i]; j<ship_number[i] * 2; j++){
				switch(i){

					//navios do tipo 0
					case 0:{
						printf("Estás a inserir um navio do tipo 0 (1x1)\n");

						//neste navio nao faz sentido pedir a rotação
						game_ship[i].rot = 0;

						flag = -1;

						//verificação dos espaços a serem ocupados pelo navio
						//se a coordenada for inválida, o ciclo diz que é invalida e pede novas instruções

						while(flag != 0){
							printf("Insere as coordenadas do navio\n");
							scanf("%d%d", &x, &y);

							//verificar se as posições de colocação sao dentro dos limites
							flag = checker(g, 0, 0, x, y);

							if(flag == -1){
								printf("Esse espaço já está ocupado, tenta outra vez!\n");
							}
						}

						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						place_boat(g, &game_ship[i], rot, x, y, 0); 
						printf("\n");
					
						break;
					}

					//navios do tipo 1
					case 1: {
						printf("Estás a inserir um navio do tipo 1 (1x2)\n");

						//rotação do navio
						printf("Insere o valor da rotação que pretendes(0, 90, 180, 270 ou 360)\n");
						scanf("%d", &rot);
						

						if((rot != 0) && (rot != 90) && (rot != 180) && (rot != 270) && (rot != 360)){
							printf("Valor de rotação inválido. Será usada rotação de 0 graus\n");
							rot = 0;
						}

						game_ship[i].rot = rot;

						flag = -1;

						//verificação dos espaços a serem ocupados pelo navio
						//se a coordenada for inválida, o ciclo diz que é invalida e pede novas instruções
						
						while(flag != 0){
							printf("Insere as coordenadas do navio\n");
							scanf("%d%d", &x, &y);

							//verificar se as posições de colocação sao dentro dos limites
							flag = checker(g, 1, rot, x, y);

							if(flag == -1){
								printf("Esse espaço já está ocupado, tenta outra vez!\n");
							}
						}

						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						place_boat(g, &game_ship[i], rot, x, y, 1); 
						printf("\n");
						break;
					}

					//navios do tipo 2
					case 2:{
						printf("Estás a inserir um navio do tipo 2 (1x3)\n");

						//rotação do navio
						printf("Insere o valor da rotação que pretendes(0, 90, 180, 270 ou 360)\n");
						scanf("%d", &rot);

						if((rot != 0) && (rot != 90) && (rot != 180) && (rot != 270) && (rot != 360)){
							printf("Valor de rotação inválido. Será usada rotação de 0 graus\n");
							rot = 0;
			     		}

						game_ship[i].rot = rot;

						flag = -1;

						//verificação dos espaços a serem ocupados pelo navio
						//se a coordenada for inválida, o ciclo diz que é invalida e pede novas instruções
						
						while(flag != 0){
							printf("Insere as coordenadas do navio\n");
							scanf("%d%d", &x, &y);

							//verificar se as posições de colocação sao dentro dos limites
							flag = checker(g, 2, rot, x, y);

							if(flag == -1){
								printf("Esse espaço já está ocupado, tenta outra vez!\n");
							}
						}

						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						place_boat(g, &game_ship[i], rot, x, y, 2); 
						printf("\n");
						break;
						
					}

					//navios do tipo 3
					case 3:{
						printf("Estás a inserir um navio do tipo 3 (1x4)\n");

						//rotação do navio
						printf("Insere o valor da rotação que pretendes(0, 90, 180, 270 ou 360)\n");
						scanf("%d", &rot);

						if((rot != 0) && (rot != 90) && (rot != 180) && (rot != 270) && (rot != 360)){
							printf("Valor de rotação inválido. Será usada rotação de 0 graus\n");
							rot = 0;
			     		}

						game_ship[i].rot = rot;

						flag = -1;

						//verificação dos espaços a serem ocupados pelo navio
						//se a coordenada for inválida, o ciclo diz que é invalida e pede novas instruções
						
						while(flag != 0){
							printf("Insere as coordenadas do navio\n");
							scanf("%d%d", &x, &y);

							//verificar se as posições de colocação sao dentro dos limites
							flag = checker(g, 3, rot, x, y);

							if(flag == -1){
								printf("Esse espaço já está ocupado, tenta outra vez!\n");
							}
						}

						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						place_boat(g, &game_ship[i], rot, x, y, 3); 
						printf("\n");
						break;
					}
					default: break;
				}
			}
		}
	}


 //----------------------------------------------------------------------------------------------------


	//colocar os barcos aleatoriamente
	else {

		/*colocação dos navios em L
		colocamos primeiro os navios em L porque sao os que ocupam mais espaço
		logo, com o tabuleiro vazio, há mais espaço para ocuparem*/

		for(int i = ship_number[4]; i<2*ship_number[4]; i++){
			//rotação do navio
			int r = rand() % 4;

			int rot = choose(r);

			game_ship[i].rot = rot;

			flag = -1;

			//verificação dos espaços a serem ocupados pelo navio
			//se a coordenada for inválida, o ciclo diz que é invalida e pede novas instruções
			while(flag != 0){
				x = rand() % (g->b_size);
				y = rand() % (g->b_size);

				flag = check1(x, y, g->b_size);

				if(flag != -1){
					//verificar se as posições de colocação não colidem com outro navio
					flag = checker(g, 4, rot, x, y);
				}	
			}

			/*neste ponto, as posições necessárias para inserção
			já foram verificadas*/

			place_boat(g, &game_ship[i], rot, x, y, 4); 
		}
		

		/*inserção dos restantes navio
		fazemos depois porque são mais simples 
		de inserir*/

		for(int i = 0; i<4; i++){
			for(int j = ship_number[i]; j<ship_number[i] * 2; j++){
				switch(i){

					//navios do tipo 0
					case 0:{
						
						game_ship[i].rot = 0;

						flag = -1;

						//verificação dos espaços a serem ocupados pelo navio
						//se a coordenada for inválida, o ciclo continua e procura por uma posição válida
						while(flag != 0){
							x = rand() % (g->b_size);
							y = rand() % (g->b_size);

							flag = check1(x, y, g->b_size);

							if(flag != -1){
								//verificar se as posições de colocação não colidem com outro navio
								flag = checker(g, 0, rot, x, y);
							}	
						}

						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						place_boat(g, &game_ship[i], rot, x, y, 0); 
					
						break;
					}

					//navios do tipo 1
					case 1: {
						
						//rotação do navio
						int r = rand() % 4;

						rot = choose(r);

						game_ship[i].rot = rot;

						flag = -1;

						//verificação dos espaços a serem ocupados pelo navio
						//se a coordenada for inválida, o ciclo procura novas coordenadas
						while(flag != 0){

							x = rand() % (g->b_size);
							y = rand() % (g->b_size);

							flag = check1(x, y, g->b_size);

							//verificar se as posições de colocação não colidem com outro navio
							if(flag != -1){
								flag = checker(g, 1, rot, x, y);
							}
						}


						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						place_boat(g, &game_ship[i], rot, x, y, 1); 
						printf("\n");
						break;
					}

					//navios do tipo 2
					case 2:{
									
						//rotação do navio
						int r = rand() % 4;

						rot = choose(r);

						game_ship[i].rot = rot;

						flag = -1;

						//verificação dos espaços a serem ocupados pelo navio
						//se a coordenada for inválida, o ciclo diz que é invalida e pede novas instruções
						while(flag != 0){

							x = rand() % (g->b_size);
							y = rand() % (g->b_size);

							flag = check1(x, y, g->b_size);

							if(flag != -1){
								//verificar se as posições de colocação não colidem com outro navio
								flag = checker(g, 2, rot, x, y);
							}	
						}


						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						place_boat(g, &game_ship[i], rot, x, y, 2); 
						break;		
					}

					//navios do tipo 3
					case 3:{
						
						//rotação do navio
						int r = rand() % 4;

						rot = choose(r);

						game_ship[i].rot = rot;

						flag = -1;

						//verificação dos espaços a serem ocupados pelo navio
						while(flag != 0){

							x = rand() % (g->b_size);
							y = rand() % (g->b_size);

							flag = check1(x, y, g->b_size);

							if(flag != -1){
								//verificar se as posições de colocação não colidem com outro navio
								flag = checker(g, 4, rot, x, y);
							}	
						}

						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						place_boat(g, &game_ship[i], rot, x, y, 3); 
						break;
					}
					default: break;
				}
			}
		}	
	}
}

//----------------------------------------------------------------------------------------------
//motor de jogo.

void moving_x_y(Game* g, int x, int y){
	int tipo = g->board[x][y].pointer_ship->tipo;

	switch(tipo){

		case 0:{
			/*como é um barco 1x1, a vida será retirada e fica logo a 0,
			logo não são necessárias transformações*/
			break;
		}

		case 1:{
			g->board[x][y].pointer_ship->x++;
			break;
		}

		case 2:{
			g->board[x][y].pointer_ship->x++;
			break;
		}

		case 3:{
			g->board[x][y].pointer_ship->x++;
			break;
		}

		case 4:{
			if((g->board[x][y].pointer_ship->x)<3)
				g->board[x][y].pointer_ship->x++;

			else 
				g->board[x][y].pointer_ship->y++;
			
			break;
		}

		default: break;
	}
}

//validação das coordenadas inseridas
char* validate_coord(int size, int x, int y){
	if(x < 0 || y < 0 || x > (size-1) || y > (size-1))
		return NULL;

	char* a = "123 123";
	return a; 
}

void print_state(Game* g1, Game* g2){
	printf("O teu tabuleiro:\n");
	for(int i = 0; i<g1->b_size; i++){
		for(int j = 0; j<g1->b_size; j++){
			if(g1->board[i][j].pointer_ship != NULL){
				if(g2->board[i][j].shoot == 0){
					printf("1");
				}

				if(g2->board[i][j].shoot == 2){
					printf("2");
				}
			}

			if(g1->board[i][j].pointer_ship == NULL){
				if(g2->board[i][j].shoot == 1){
					printf("3");
				}
				else {
					printf("%d", g2->board[i][j].shoot);
				}
			}
		}
		printf("\n");
	}

	printf("\n");

	printf("O que sabes do teu adversário!\n");
	for(int i = 0; i<g1->b_size; i++){
		for(int j = 0; j<g1->b_size; j++){
			if(g1->board[i][j].shoot == 1){
				printf("3");
			}
			else {
				printf("%d", g1->board[i][j].shoot);
			}
		}
		printf("\n");
	}

}

//função do jogo 
void play(Game* P1, Game* P2){
	int x = 0;
	int y = 0;
	int turn = 1;
	int temp1 = 0; 
	int temp2 = 0;

	while(1){


		//turno do jogador número 1
		if(turn == 1){
			
			printf("É a tua vez, jogador 1.\n");
			print_state(P1, P2);
			printf("\n");
			printf("Insere a coordenada que pretendes atacar!\n");
			scanf("%d%d", &x, &y);

			char* a = validate_coord(P1->b_size, x, y);

			if(a == NULL){
				printf("Coordenada inválida. Perdeste a tua vez.\n\n");
				turn = 2;
				continue;
			}

			if (P1->board[x][y].shoot != 0){
				printf("Já atingis-te essa coordenada! Perdeste a tua vez!\n\n");
				turn = 2;
				continue;
			}

			

			if(P2->board[x][y].pointer_ship == NULL){
				printf("Miss\n");
				P1->board[x][y].shoot = 1;
			}

			else{
				printf("Hit\n");

				P1->board[x][y].shoot = 2;

				temp1 = P2->board[x][y].pointer_ship->x;
				temp2 = P2->board[x][y].pointer_ship->y;

				P2->board[x][y].pointer_ship->bitmap[temp1][temp2] = '2';

				P2->board[x][y].pointer_ship->ship_health--;


				if(P2->board[x][y].pointer_ship->ship_health == 0){
					printf("Afundas-te um barco!\n");
					P2->ship_count--;
				}
				

				else {
					moving_x_y(P2, x, y); //recolocar x e y para proximas jogadas
				}
				
			}

			turn = 2;
		}

		//turno do jogador número 2
		else if(turn == 2){

			printf("É a tua vez, jogador 2.\n");
			print_state(P2, P1);
			printf("\n");
			printf("Insere a coordenada que pretendes atacar!\n");
			scanf("%d%d", &x, &y);

			char* a = validate_coord(P1->b_size, x, y);

			

			if (P2->board[x][y].shoot != 0){
				printf("Já atingis-te essa coordenada! Perdeste a tua vez!\n");
				turn = 2;
				continue;
			}

			if(a == NULL) {
				printf("Coordenada inválida. Perdeste a tua vez.\n");
				turn = 1;
				continue;
			}

			
			if(P1->board[x][y].pointer_ship == NULL){
				printf("Miss\n");
				P2->board[x][y].shoot = 1;
			}

			else{
				printf("Hit\n");

				P2->board[x][y].shoot = 2;

				temp1 = P1->board[x][y].pointer_ship->x;

				temp2 = P1->board[x][y].pointer_ship->y;

				P1->board[x][y].pointer_ship->bitmap[temp1][temp2] = '2';

				P1->board[x][y].pointer_ship->ship_health--;	


				if(P1->board[x][y].pointer_ship->ship_health == 0){
					printf("Afundas-te um barco!\n");
					P1->ship_count--;
				}
				
				else {
					moving_x_y(P1, x, y); //recolocar x e y para proximas jogadas
				}
			}
			turn = 1;
		}
		

		//se algum dos jogadores ficar sem navios, o jogo acaba!
		if(P1->ship_count == 0){
			printf("Parabéns jogador 2, Ganhaste!!\n");
			break;
		}
		else if(P2->ship_count == 0){
			printf("Parabéns jogador 1, Ganhaste!!\n");
			break;
		}
	}
}

//libertação de memória alocada dinamicamente

void memory_free(Game *g1, Game *g2, Ship *a1, Ship *a2){
	free(a1);
	free(a2);

	for(int i = 0; i<g1->b_size; i++){
		free(g1->board[i]);
		free(g2->board[i]);
	}

	free(g1->board);
	free(g2->board);

	free(g1);
	free(g2);
}