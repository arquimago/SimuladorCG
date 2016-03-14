#include "Ecossistema.h"


Ecossistema::inicializar (x, y, z)
{
    aquario.dimensao = new plano[y+2];
        for(int i = 0; i < y+2; i++){
            aquario.dimensao[i].grid = new unidade[x+2,z+2];
        }
        for(int i = 0; i < y+2; i++){
            for(int j = 0; j < x+2; j++){
                for(int k = 0; k < z+2; k++){
                    if(i==0||i==y+1||j==0||j==x+1||k==0||k==z+1){
                        aquario.dimensao[i].grid[j,k].ocupante[0] = new Posicionavel('r');
                        aquario.dimensao[i].grid[j,k].ocupante[1] = NULL;
                    } else {
                        aquario.dimensao[i].grid[j,k].ocupante[0] = NULL;
                        aquario.dimensao[i].grid[j,k].ocupante[1] = NULL;
                    }
                }
            }
        }
}

Ecossistema::identificarOcupantes()
{


}


Ecossistema::~Ecossistema()
{
    //dtor
}
