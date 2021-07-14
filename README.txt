Projeto LabP 2019/2020 || Parte B || TP2_O ||

Compilação e execução:
Compilar com suporte para quadTree: make
Compilar com suporte para matriz: make batalha_matrix
Executar: ./BattleShip
Todos os ficheiros devem estar no mesmo diretório

Os ficheiros ._* têm de estar no diretório devido a erros de compilação que estavam a acontecer.

Módulos existentes:
Point: Guarda a estrutura ponto e todas as funções relativas a pontos.
quadTree: Guarda a estrutura da quadTree, bem como as estruturas de jogo (Cell, Game e Ship)
game: Guarda as funções relativas ao suporte em quadTree
SeaBattle: Guarda as funções relativas ao suporte em matriz

BUG conhecido: o navio em L, no suporte com quadTree, por vezes fica com posições ocultas ou diferentes das que eram suposto ser, apesar de haver instrução para as inserir.

Todos os ficheiros têm comentários a explicar o que cada função faz, e os nomes das funções são intuitivos.