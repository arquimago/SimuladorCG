#include "Posicionavel.h"
#ifndef ECOSSISTEMA_H
#define ECOSSISTEMA_H


// definicoes para montar o cubo
//unidade minima do cubo.
typedef struct {
	 bool ocupada;
	 Posicionavel* ocupante;//uma variavel ponteiro para a classe posicionavel, pai de todas as outras 3 classes
} unidade;

//plano formado pelas unidades minimas
typedef struct {
	 unidade* grid; // matriz [x][y] de variaveis local
} plano;

//cubo formado pelos planos
typedef struct {
	  plano* dimensao; //vetor de [z] planos
} cubo;


// a ideia dessa classe é armazenar o "mapa" do ecossistema, localizações com ponteiros para os respectivos objetos
class Ecossistema
{
	public:
		static cubo aquario;

		static void inicializar (int x, int y, int z); // grid = new unidade [x,y];   dimensao = new plano [z];

		static Posicionavel* identificarOcupante(int x, int y, int z);// retorna quem ocupa o local   retorna null se não tem

};

#endif // ECOSSISTEMA_H

