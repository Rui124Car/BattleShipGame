#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int qt_size; //size da qtree -> 32 ou 64


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

//criação de um estado de jogo
Game *new_game(int size, int ship_number){
	Game *g = (Game*) malloc(sizeof(Game));
	g->ship_number = ship_number;
	g->b_size = size;

	if(size > 32)
		qt_size = 64;
	else
		qt_size = 32;

	g->board = NULL;
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

//ship_number -> quantidade de navios do tipo i
//game_ship -> os navios já criados e prontos para inserção

int check1(int x, int y, int size){
 	if((x > 2) && (x < (size - 2)) && (y > 2) && (y < (size - 2)))
 		return 0;

	return -1;
}

int pos_checker(int x, int y, QD_NODE *root){
	Point p = make_point(x, y);
	Point sw = make_point(0,0);

	Point multiplier[3];

	multiplier[0] = make_point(1,0);
	multiplier[1] = make_point(0,1);
	multiplier[2] = make_point(1,1);

	QD_NODE *temp = QD_SEARCH(root, p, qt_size, sw, multiplier);

	if(temp != NULL){
		free(temp);
		return -1;
	}

	free(temp);
	return 1;
}

Cell *create_cell(Ship *ship, int shoot){
	Cell *new_cell = (Cell*) malloc(sizeof(Cell));
	new_cell->pointer_ship = ship;
	new_cell->shoot = shoot;

	return new_cell;
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

QD_NODE *place_boat(Game *g, Ship *ship, int rot, int x, int y, int tipo){
	Point sw = make_point(0,0);
	Point multiplier[3];

	multiplier[0] = make_point(1,0);
	multiplier[1] = make_point(0,1);
	multiplier[2] = make_point(1,1);

	switch(tipo){
		case 0: {
			Cell *pos = create_cell(ship, 0);
			Point p = make_point(x, y);
			g->board = QD_INSERT(g->board, p, pos, sw, qt_size, multiplier);
			return g->board;
		}
		case 1:	{
			if(rot == 0 || rot == 360){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Point p1 = make_point(x, y);
				Point p2 = make_point(x+1, y);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				return g->board;
			}

			else if(rot == 90){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Point p1 = make_point(x, y);
				Point p2 = make_point(x, y+1);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				return g->board;
			}

			else if(rot == 180){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Point p1 = make_point(x, y);
				Point p2 = make_point(x-1, y);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				return g->board;
			}

			else if(rot == 270){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Point p1 = make_point(x, y);
				Point p2 = make_point(x, y-1);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				return g->board;
			}

			break;
		}

		case 2:	{
			if(rot == 0 || rot == 360 || rot == 180){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Cell *pos3 = create_cell(ship, 0);
				Point p1 = make_point(x, y);
				Point p2 = make_point(x+1, y);
				Point p3 = make_point(x-1, y);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p3, pos3, sw, qt_size, multiplier);
				return g->board;
			}

			else if(rot == 90 || rot == 270){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Cell *pos3 = create_cell(ship, 0);
				Point p1 = make_point(x, y);
				Point p2 = make_point(x, y+1);
				Point p3 = make_point(x, y-1);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p3, pos3, sw, qt_size, multiplier);
				return g->board;
			}

			break;
		}

		case 3:	{
			if(rot == 0 || rot == 360){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Cell *pos3 = create_cell(ship, 0);
				Cell *pos4 = create_cell(ship, 0);
				Point p1 = make_point(x,y);
				Point p2 = make_point(x+1,y);
				Point p3 = make_point(x+2,y);
				Point p4 = make_point(x-1,y);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p3, pos3, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p4, pos4, sw, qt_size, multiplier);
				return g->board;
			}

			else if(rot == 90){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Cell *pos3 = create_cell(ship, 0);
				Cell *pos4 = create_cell(ship, 0);
				Point p1 = make_point(x, y);
				Point p2 = make_point(x, y+1);
				Point p3 = make_point(x, y+2);
				Point p4 = make_point(x, y-1);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p3, pos3, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p4, pos4, sw, qt_size, multiplier);
				return g->board;
			}

			else if(rot == 180){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Cell *pos3 = create_cell(ship, 0);
				Cell *pos4 = create_cell(ship, 0);
				Point p1 = make_point(x, y);
				Point p2 = make_point(x-1, y);
				Point p3 = make_point(x-2, y);
				Point p4 = make_point(x+1, y);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p3, pos3, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p4, pos4, sw, qt_size, multiplier);
				return g->board;
			}

			else if(rot == 270){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Cell *pos3 = create_cell(ship, 0);
				Cell *pos4 = create_cell(ship, 0);
				Point p1 = make_point(x, y);
				Point p2 = make_point(x, y-1);
				Point p3 = make_point(x, y-2);
				Point p4 = make_point(x, y+1);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p3, pos3, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p4, pos4, sw, qt_size, multiplier);
				return g->board;
			}

			break;
		}

		case 4:	{
			if(rot == 0 || rot == 360){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Cell *pos3 = create_cell(ship, 0);
				Cell *pos4 = create_cell(ship, 0);
				Cell *pos5 = create_cell(ship, 0);
				Point p1 = make_point(x, y);
				Point p2 = make_point(x-1, y);
				Point p3 = make_point(x+1, y);
				Point p4 = make_point(x+1, y+1);
				Point p5 = make_point(x+1, y+2);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p3, pos3, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p4, pos4, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p5, pos5, sw, qt_size, multiplier);
				return g->board;
			}

			else if(rot == 90){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Cell *pos3 = create_cell(ship, 0);
				Cell *pos4 = create_cell(ship, 0);
				Cell *pos5 = create_cell(ship, 0);
				Point p1 = make_point(x, y);
				Point p2 = make_point(x, y-1);
				Point p3 = make_point(x, y+1);
				Point p4 = make_point(x-1, y+1);
				Point p5 = make_point(x-2, y+1);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p3, pos3, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p4, pos4, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p5, pos5, sw, qt_size, multiplier);
				return g->board;
			}

			else if(rot == 180){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Cell *pos3 = create_cell(ship, 0);
				Cell *pos4 = create_cell(ship, 0);
				Cell *pos5 = create_cell(ship, 0);
				Point p1 = make_point(x, y);
				Point p2 = make_point(x-1, y);
				Point p3 = make_point(x+1, y);
				Point p4 = make_point(x+1, y-1);
				Point p5 = make_point(x-1, y-2);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p3, pos3, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p4, pos4, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p5, pos5, sw, qt_size, multiplier);
				return g->board;
			}

			else if(rot == 270){
				Cell *pos1 = create_cell(ship, 0);
				Cell *pos2 = create_cell(ship, 0);
				Cell *pos3 = create_cell(ship, 0);
				Cell *pos4 = create_cell(ship, 0);
				Cell *pos5 = create_cell(ship, 0);
				Point p1 = make_point(x, y);
				Point p2 = make_point(x, y-1);
				Point p3 = make_point(x, y+1);
				Point p4 = make_point(x+1, y-1);
				Point p5 = make_point(x+2, y-1);
				g->board = QD_INSERT(g->board, p1, pos1, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p2, pos2, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p3, pos3, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p4, pos4, sw, qt_size, multiplier);
				g->board = QD_INSERT(g->board, p5, pos5, sw, qt_size, multiplier);
				return g->board;
			}

			break;
		}
		default: return g->board;
	}
	return g->board;
}

int checker(QD_NODE *root, Point p, int rot, int tipo){

	switch(tipo){

		//barco do tipo 0
		case 0:{

			int ver = pos_checker(p.x, p.y, root); //x;y

			return ver;
		 	break;
		}


		//barco do tipo 1
		case 1: {

			if(rot == 0 || rot == 360){
				int ver = pos_checker(p.x, p.y, root); //x;y
				if(ver == -1)
					return -1;

				ver = pos_checker(p.x+1, p.y, root); //x+1;y
				if(ver == -1)
					return -1;

				return 0;
			}

			else if(rot == 90){

				int ver = pos_checker(p.x, p.y, root); //x;y
				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y+1, root); //x;y+1
				if(ver == -1)
					return -1;

				return 0;
			}

			else if(rot == 180){

				int ver = pos_checker(p.x, p.y, root); //x;y
				if(ver == -1)
					return -1;

				ver = pos_checker(p.x-1, p.y, root);	//x-1;y
				if(ver == -1)
					return -1;

				return 0;
			}

			else if(rot == 270){

				int ver = pos_checker(p.x, p.y, root); //x;y
				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y-1, root);	//x;y-1
				if(ver == -1)
					return -1;

				return 0;
			}

			break;
		}

		//barco do tipo 2
		case 2:	{
			if(rot == 0 || rot == 360 || rot == 180){

				int ver = pos_checker(p.x, p.y, root); //x;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x+1, p.y, root);	//x+1;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x-1, p.y, root);	//x-1;y

				if(ver == -1)
					return -1;

				return 0;
			
			}

			else if(rot == 90 || rot == 270){
				int ver = pos_checker(p.x, p.y, root);	//x;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y+1, root);	//x;y+1

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y-1, root);	//x;y-1

				if(ver == -1)
					return -1;

				return 0;
			}

			break;
		}


		//barcos do tipo 3
		case 3:	{

			if(rot == 0 || rot == 360){

				int ver = pos_checker(p.x, p.y, root); //x;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x+1, p.y, root);	//x+1;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x-1, p.y, root);	//x-1;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x+2, p.y, root);	//x+2;y

				if(ver == -1)
					return -1;

				return 0;
			
			}

			else if(rot == 90){

				int ver = pos_checker(p.x, p.y, root); //x;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y-1, root);	//x+1;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y+1, root);	//x;y+1

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y+2, root);	//x;y+2

				if(ver == -1)
					return -1;

				return 0;
			
			}

			else if(rot == 180){

				int ver = pos_checker(p.x, p.y, root); //x;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x+1, p.y, root);	//x+1;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x-1, p.y, root);	//x-1;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x-2, p.y, root);	//x-2;y

				if(ver == -1)
					return -1;

				return 0;
			
			}

			else if(rot == 270){

				int ver = pos_checker(p.x, p.y, root); //x;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y-1, root);	//x;y-1

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y+1, root);	//x;y+1

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y-2, root);	//x;y-2

				if(ver == -1)
					return -1;

				return 0;
			}

			break;
		}


		//barcos do tipo 4
		case 4:	{

			if(rot == 0 || rot == 360){

				int ver = pos_checker(p.x, p.y, root); //x;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x+1, p.y, root);	//x+1;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x-1, p.y, root);	//x-1;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x+1, p.y+1, root);	//x+1;y+1

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x+1, p.y+2, root);	//x+1;y+2

				if(ver == -1)
					return -1;

				return 0;
			
			}

			else if(rot == 90){

				int ver = pos_checker(p.x, p.y, root); //x;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y-1, root);	//x;y-1

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y+1, root);	//x;y+1

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x-2, p.y+1, root);	//x-2;y+1

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x-1, p.y+1, root);	//x-1;y+1

				if(ver == -1)
					return -1;

				return 0;
			
			}

			else if(rot == 180){

				int ver = pos_checker(p.x, p.y, root); //x;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x+1, p.y, root);	//x+1;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x-1, p.y, root);	//x-1;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x-1, p.y-1, root);	//x-1;y-1

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x-1, p.y-2, root);	//x-1;y-2

				if(ver == -1)
					return -1;

				return 0;
			
			}

			else if(rot == 270){

				int ver = pos_checker(p.x, p.y, root); //x;y

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y-1, root);	//x;y-1

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x, p.y+1, root);	//x;y+1

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x+1, p.y-1, root);	//x+1;y-1

				if(ver == -1)
					return -1;

				ver = pos_checker(p.x+2, p.y-1, root);	//x+2;y-1

				if(ver == -1)
					return -1;

				return 0;
			}


			break;
		}

		default: return -1;;
	}
	return -1;
}


void space_check_boat_placement(int game_mode, int ship_number[], Game *g, Ship* game_ship){
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

				Point p = make_point(x, y);

				//verificar se as posições de colocação não colidem com outro navio
				flag = checker(g->board, p, rot, 4);

				if(flag == -1){
					printf("Esse espaço é inválido, tenta outra vez!\n");
				}
			}

			/*neste ponto, as posições necessárias para inserção
			já foram verificadas*/

			g->board = place_boat(g, &game_ship[i], rot, x, y, 4);
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
							Point p = make_point(x, y);

							//verificar se as posições de colocação não colidem com outro navio
							flag = checker(g->board, p, rot, 0);

							if(flag == -1){
								printf("Esse espaço é inválido, tenta outra vez!\n");
							}
						}

						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						g->board = place_boat(g, &game_ship[i], rot, x, y, 0);
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
							Point p = make_point(x, y);

							//verificar se as posições de colocação não colidem com outro navio
							flag = checker(g->board, p, rot, 1);

							if(flag == -1){
								printf("Esse espaço é inválido, tenta outra vez!\n");
							}

						}

						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						g->board = place_boat(g, &game_ship[i], rot, x, y, 1);
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
							Point p = make_point(x, y);

							//verificar se as posições de colocação não colidem com outro navio
							flag = checker(g->board, p, rot, 2);

							if(flag == -1){
								printf("Esse espaço é inválido, tenta outra vez!\n");
							}

						}

						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						g->board = place_boat(g, &game_ship[i], rot, x, y, 2);
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
							
							Point p = make_point(x, y);

							//verificar se as posições de colocação não colidem com outro navio
							flag = checker(g->board, p, rot, 4);

							if(flag == -1){
								printf("Esse espaço é inválido, tenta outra vez!\n");
							}

						}

						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						g->board = place_boat(g, &game_ship[i], rot, x, y, 3);
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
					Point p = make_point(x, y);

					//verificar se as posições de colocação não colidem com outro navio
					flag = checker(g->board, p, rot, 4);
				}	
			}

			/*neste ponto, as posições necessárias para inserção
			já foram verificadas*/

			g->board = place_boat(g, &game_ship[i], rot, x, y, 4);
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
						while(flag == -1){
							x = rand() % (g->b_size);
							y = rand() % (g->b_size);

							flag = check1(x, y, g->b_size);

							if(flag != -1){
								Point p = make_point(x, y);

								//verificar se as posições de colocação não colidem com outro navio
								flag = checker(g->board, p, rot, 0);

							}	
						}

						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						g->board = place_boat(g, &game_ship[i], rot, x, y, 0);
					
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

							if(flag != -1){
								Point p = make_point(x, y);

								//verificar se as posições de colocação não colidem com outro navio
								flag = checker(g->board, p, rot, 1);
							}
						}


						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						g->board = place_boat(g, &game_ship[i], rot, x, y, 1);
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
								Point p = make_point(x, y);

								//verificar se as posições de colocação não colidem com outro navio
								flag = checker(g->board, p, rot, 2);
							}	
						}


						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						g->board = place_boat(g, &game_ship[i], rot, x, y, 2);
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
								Point p = make_point(x, y);

								//verificar se as posições de colocação não colidem com outro navio
								flag = checker(g->board, p, rot, 3);
							}	
						}

						/*neste ponto, as posições necessárias para inserção
						já foram verificadas*/

						g->board = place_boat(g, &game_ship[i], rot, x, y, 3);
						break;
					}
					default: break;
				}
			}
		}	
	}
}


/////////////////////////////////////motor do jogo//////////////////////////////////////
void moving_x_y(Game* g, int x, int y){
	Point multiplier[3];

	multiplier[0] = make_point(1,0);
	multiplier[1] = make_point(0,1);
	multiplier[2] = make_point(1,1);
	Point p = make_point(x,y);
	Point sw = make_point(0,0);


	QD_NODE *help = QD_SEARCH(g->board, p, qt_size, sw, multiplier);
	int tipo = help->node.leaf.pos->pointer_ship->tipo;

	switch(tipo){

		case 0:{
			/*como é um barco 1x1, a vida será retirada e fica logo a 0,
			logo não são necessárias transformações*/
			break;
		}

		case 1:
		case 2:
		case 3:{
			help->node.leaf.pos->pointer_ship->x++;
			break;
		}
		case 4:{
			if(help->node.leaf.pos->pointer_ship->x < 3)
				help->node.leaf.pos->pointer_ship->x++;

			else 
				help->node.leaf.pos->pointer_ship->y++;
			
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

void print_state(Game *g1, Game *g2){
	printf("O teu tabuleiro:                                            ");
	printf("O que sabes do teu adversário:\n");

	QD_NODE *help1;
	QD_NODE *help2;
	Point multiplier[3];

	multiplier[0] = make_point(1,0);
	multiplier[1] = make_point(0,1);
	multiplier[2] = make_point(1,1);

	Point sw = make_point(0,0);
	for(int i = 0; i<g1->b_size; i++){
		for(int j = 0; j<g1->b_size; j++){

			Point p = make_point(i, j);
			help1 = QD_SEARCH(g1->board, p, qt_size, sw, multiplier);
			help2 = QD_SEARCH(g2->board, p, qt_size, sw, multiplier);
			if(help1 == NULL && help2 == NULL)
				printf("0");

			else if (help2 == NULL && help1 != NULL)
				printf("1");

			else if(help2 != NULL && help1 != NULL){
				if(help2->node.leaf.pos->shoot == 0)
					printf("0");
				else if(help2->node.leaf.pos->shoot == 1)
					printf("3");
				else if(help2->node.leaf.pos->shoot == 2)
					printf("2");
			}
			else
				printf("0");
		}
		printf("                                        ");
		for(int j = 0; j<g1->b_size; j++){

			Point p = make_point(i, j);
			help1 = QD_SEARCH(g1->board, p, qt_size, sw, multiplier);
			help2 = QD_SEARCH(g2->board, p, qt_size, sw, multiplier);
			
				if (help1 == NULL)
					printf("0");

				else if (help1->node.leaf.pos->shoot == 0)
					printf("0");

				else if(help1->node.leaf.pos->shoot == 1)
					printf("3");
				
				
				else if(help1->node.leaf.pos->shoot == 2)
					printf("2");
			}
		printf("\n");
	}
}

void play(Game *P1, Game *P2){
	printf("\n");
	int x = 0;
	int y = 0;
	int turn = 1;
	int temp1 = 0; 
	int temp2 = 0;
	QD_NODE *helpP1;
	QD_NODE *helpP2;
	Point p;
	Point sw = make_point(0,0);


	Point multiplier[3];

	multiplier[0] = make_point(1,0);
	multiplier[1] = make_point(0,1);
	multiplier[2] = make_point(1,1);

	while(1){


		//turno do jogador número 1
		if(turn == 1){
			
			printf("É a tua vez, jogador 1.\n");
			print_state(P1, P2);
			printf("\n");
			printf("Insere a coordenada que pretendes atacar!\n");
			scanf("%d%d", &x, &y);
			p = make_point(x,y);
			helpP1 = QD_SEARCH(P1->board, p, qt_size, sw, multiplier);
			helpP2 = QD_SEARCH(P2->board, p, qt_size, sw, multiplier);

			char* a = validate_coord(P1->b_size, x, y);

			if(a == NULL){
				printf("Coordenada inválida. Perdeste a tua vez.\n\n");
				turn = 2;
				continue;
			}

			if ((helpP1 != NULL) && (helpP1->node.leaf.pos->shoot != 0)){
				printf("Já atingis-te essa coordenada! Perdeste a tua vez!\n\n");
				turn = 2;
				continue;
			}

			if(helpP2 == NULL){

				//se não existir essa posição ainda, criamos, se já existir só mudamos o campo shoot
				if(helpP1 == NULL){
					Cell *pos = create_cell(NULL, 1);
					P1->board = QD_INSERT(P1->board, p, pos, sw, qt_size, multiplier);
				}
				else 
					helpP1->node.leaf.pos->shoot = 1;

				printf("Miss\n");
				turn = 2;
				printf("\n");
				continue;
			}

			else if(helpP2->node.leaf.pos->pointer_ship == NULL){

				//se não existir essa posição ainda, criamos, se já existir só mudamos o campo shoot
				if(helpP1 == NULL){
					Cell *pos = create_cell(NULL, 1);
					P1->board = QD_INSERT(P1->board, p, pos, sw, qt_size, multiplier);
				}
				else 
					helpP1->node.leaf.pos->shoot = 1;

				printf("Miss\n");
				turn = 2;
				printf("\n");
				continue;
			}

			

			else if(helpP2->node.leaf.pos->pointer_ship != NULL){
				printf("Hit\n");

				//se não existir essa posição ainda, criamos, se já existir só mudamos o campo shoot
				if(helpP1 == NULL){
					Cell *pos = create_cell(NULL, 2);
					P1->board = QD_INSERT(P1->board, p, pos, sw, qt_size, multiplier);
				}
				else 
					helpP1->node.leaf.pos->shoot = 2;

				temp1 = helpP2->node.leaf.pos->pointer_ship->x;
				temp2 = helpP2->node.leaf.pos->pointer_ship->x;

				helpP2->node.leaf.pos->pointer_ship->bitmap[temp1][temp2] = '2';

				helpP2->node.leaf.pos->pointer_ship->ship_health--;


				if(helpP2->node.leaf.pos->pointer_ship->ship_health == 0) {
					printf("Afundas-te um navio!\n");
					P2->ship_number--;
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

			if(a == NULL){
				printf("Coordenada inválida. Perdeste a tua vez.\n\n");
				turn = 2;
				continue;
			}

			p = make_point(x,y);
			helpP1 = QD_SEARCH(P1->board, p, qt_size, sw, multiplier);
			helpP2 = QD_SEARCH(P2->board, p, qt_size, sw, multiplier);

			if ((helpP2 != NULL) && (helpP2->node.leaf.pos->shoot != 0)){
				printf("Já atingis-te essa coordenada! Perdeste a tua vez!\n\n");
				turn = 2;
				continue;
			}

			if(helpP1 == NULL){

				//se não existir essa posição ainda, criamos, se já existir só mudamos o campo shoot
				if(helpP2 == NULL){
					Cell *pos = create_cell(NULL, 1);
					P2->board = QD_INSERT(P2->board, p, pos, sw, qt_size, multiplier);
				}
				else 
					helpP2->node.leaf.pos->shoot = 1;

				printf("Miss\n");
				turn = 1;
				printf("\n");
				continue;
			}

			else if(helpP1->node.leaf.pos->pointer_ship == NULL){
				
				//se não existir essa posição ainda, criamos, se já existir só mudamos o campo shoot
				if(helpP2 == NULL){
					Cell *pos = create_cell(NULL, 1);
					P2->board = QD_INSERT(P2->board, p, pos, sw, qt_size, multiplier);
				}
				else 
					helpP2->node.leaf.pos->shoot = 1;

				printf("Miss\n");
				turn = 1;
				printf("\n");
				continue;
			}

			

			else if(helpP1->node.leaf.pos->pointer_ship != NULL){
				printf("Hit\n");

				//se não existir essa posição ainda, criamos, se já existir só mudamos o campo shoot
				if(helpP2 == NULL){
					Cell *pos = create_cell(NULL, 2);
					P2->board = QD_INSERT(P2->board, p, pos, sw, qt_size, multiplier);
				}
				else 
					helpP2->node.leaf.pos->shoot = 2;


				temp1 = helpP1->node.leaf.pos->pointer_ship->x;
				temp2 = helpP1->node.leaf.pos->pointer_ship->x;

				helpP1->node.leaf.pos->pointer_ship->bitmap[temp1][temp2] = '2';

				helpP1->node.leaf.pos->pointer_ship->ship_health--;


				if(helpP1->node.leaf.pos->pointer_ship->ship_health == 0){
					printf("Afundas-te um navio!\n");
					P1->ship_number--;
				}
					

				else {
					moving_x_y(P1, x, y); //recolocar x e y para proximas jogadas
				}
			}
			turn = 1;
		}
		printf("\n");
		//se algum dos jogadores ficar sem navios, o jogo acaba!
		if(P1->ship_number == 0){
			printf("Parabéns jogador 2, Ganhaste!!\n");
			break;
		}
		else if(P2->ship_number == 0){
			printf("Parabéns jogador 1, Ganhaste!!\n");
			break;
		}
	}
}

void memory_free(Game *P1, Game *P2, Ship *ship1, Ship *ship2){
	free(ship1);
	free(ship2);

	free_tree(P1->board);
	free_tree(P2->board);
}


