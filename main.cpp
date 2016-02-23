#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
	int z;
} tPos;

typedef struct {
	//posicao é absoluta
	tPos posicao;
	//direcao é +1 ou -1 em cada um dos eixos
	tPos direcao;
	int peso;
} tPeixe;

typedef struct {
	tPos posicao;
	int peso;
} tAlga;

typdef struct{
	tPos posicao;
} tPedra;

//Funcao de comparação, creio que precisaremos desse trecho de código repetidamente. Se as posicoes forem iguais retorna 1 - True, senão retorna 0 - False
int compara(tPos a, tPos b){
	int resultado;
	if (a.x == b.x && a.y == b.y && a.z == b.z){
		resultado = 1;
	} else {
		resultado = 0;
	}	
}

//função sorteia para sortear as posições iniciais, trata-se sobreposições utilizando a função compara
tPos sorteiaPos(tPos max){
	tPos resultado;
	srand (time(NULL));
	resultado.x=rand()%max.x+1;
	resultado.y=rand()%max.y+1;
	resultado.z=rand()%max.z+1;
	return resultado;
}

//funcao que retorna uma direção, pra mudar usa a funcao compara
tPos sorteiaDir(){
	tPos resultado;
	resultado.x=0;
	resultado.y=0;
	resultado.z=0;
	srand (time(NULL));
	while(resultado.x==0 && resultado.y==0 && resultado.z==0){
		resultado.x=rand()%3-1;
		resultado.y=rand()%3-1;
		resultado.z=rand()%3-1;
	}
	return resultado;
}