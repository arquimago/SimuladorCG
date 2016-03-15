/*#include "Ecossistema.h"

Ecossistema::Ecossistema()
{
    //ctor
}

Ecossistema::~Ecossistema()
{
    //dtor
}*/
#include "Ecossistema.h"
#include "stddef.h"
#include "stdio.h"

void Ecossistema::inicializar (int x, int y, int z)
{
    aquario.dimensao = new plano[y+2];
    for(int i = 0; i < y+2; i++){
        aquario.dimensao[i].grid = new unidade[x+2,z+2];
    }
    for(int i = 0; i < y+2; i++){
        for(int j = 0; j < x+2; j++){
            for(int k = 0; k < z+2; k++){
                if(i==0||i==y+1||k==0||k==z+1||j==x){
                    aquario.dimensao[i].grid[j,k].ocupante[0] = new Posicionavel('r');
                    printf("i %d j %d k % d \n", i,j,k);
                    aquario.dimensao[i].grid[j,k].ocupante[1] = NULL;
                } else {
                    aquario.dimensao[i].grid[j,k].ocupante[0] = NULL;
                    aquario.dimensao[i].grid[j,k].ocupante[1] = NULL;
                }
            }
        }
    }
}
cubo Ecossistema::aquario;
