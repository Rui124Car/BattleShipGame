batalha_quadTree: BattleShip.c quadTree.h quadTree.c Point.h game.h game.c Point.c
	gcc -g -D QTREE -o BattleShip BattleShip.c game.c quadTree.c Point.c

batalha_matrix: BattleShip.c SeaBattle.h SeaBattle.c 
	gcc -g -o BattleShip BattleShip.c SeaBattle.c