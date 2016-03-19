#include "Posicionavel.h"
#ifndef ECOSSISTEMA_H
#define ECOSSISTEMA_H


// definicoes para montar o cubo
//unidade minima do cubo.
typedef struct {
	 Posicionavel* ocupante[3];
	 //ponteiro de duas posições de posicionavel (caso de peixe+ planta)
	 // 0 é pedra
	 // 1 é planta
	 // 2 é peixe
} unidade;

//plano formado pelas unidades minimas
typedef struct {
	 unidade** grid;
	 // matriz [x][z] de variaveis local
} plano;

//cubo formado pelos planos
typedef struct {
	  plano* dimensao;
	  //vetor de [y] planos
} cubo;

// a ideia dessa classe é armazenar o "mapa" do ecossistema, localizações com ponteiros para os respectivos objetos
class Ecossistema
{
    private:
        static cubo aquario;
        static posicao limites;
	public:
	    static posicao getLimites();
		static void inicializar (int x, int y, int z);
		// grid = new unidade [x,z];   dimensao = new plano [y];
		//inicializar tudo como nulo
        // arredores de pedra
		static Posicionavel** identificarOcupantes (int x, int y, int z);
		// retorna quem ocupa o local   retorna null se não tem
        static void ocupar(int x,int y, int z, int i,Posicionavel* corpo);
        //seta posicionavel no cubo
};

#endif // ECOSSISTEMA_H

