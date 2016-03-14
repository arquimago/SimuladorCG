#include "Ecossistema.h"

/*
Ecossistema::Ecossistema()
{
    //ctor
}

Ecossistema::~Ecossistema()
{
    //dtor
}
*/

class Ecossistema
{
	public:
		static cubo aquario;

		static void inicializar (int x, int y, int z){
            aquario.dimensao = new plano[y+2];
            for(int i = 0; i < y+2; i++){
                aquario.dimensao[i].grid = new unidade[x+2,z+2];
            }
            for(int i = 0; i < y+2; i++){
                for(int j = 0; j < x+2; j++){
                    for(int k = 0; k < z+2; k++){

                    }
                }
            }


		} // grid = new unidade [x,z];   dimensao = new plano [y];
		//inicializar tudo como nulo
        // arredores de pedra
		static Posicionavel** identificarOcupantes (int x, int y, int z){


        }// retorna quem ocupa o local   retorna null se não tem

};
