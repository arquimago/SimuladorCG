/*#ifndef ECOSSISTEMA_H
#define ECOSSISTEMA_H


class Ecossistema
{
    public:
        Ecossistema();
        virtual ~Ecossistema();

    protected:

    private:
};

#endif // ECOSSISTEMA_H*/

#include "Posicionavel.h"
#ifndef ECOSSISTEMA_H
#define ECOSSISTEMA_H


// definicoes para montar o cubo
//unidade minima do cubo.
typedef struct {
	 Posicionavel* ocupante[2];//ponteiro de duas posi��es de posicionavel (caso de peixe+ planta)
} unidade;

//plano formado pelas unidades minimas
typedef struct {
	 unidade* grid; // matriz [x][z] de variaveis local
} plano;

//cubo formado pelos planos
typedef struct {
	  plano* dimensao; //vetor de [y] planos
} cubo;


// a ideia dessa classe � armazenar o "mapa" do ecossistema, localiza��es com ponteiros para os respectivos objetos
class Ecossistema
{
	public:
		static cubo aquario;


		static void inicializar (int x, int y, int z); // grid = new unidade [x,z];   dimensao = new plano [y];
		//inicializar tudo como nulo
        // arredores de pedra
		static Posicionavel** identificarOcupantes (int x, int y, int z);// retorna quem ocupa o local   retorna null se n�o tem

};

#endif // ECOSSISTEMA_H
