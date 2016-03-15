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
    y+=2;
    x+=2;
    z+=2;

    aquario.dimensao = new plano[y];

    for(int i = 0; i < y; i++){
        aquario.dimensao[i].grid = new unidade*[x];
    }

    for(int i = 0; i < y; i++) {
        for(int j = 0; j < x; j++){
            aquario.dimensao[i].grid[j] = new unidade[z];
        }
    }

    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            for(int k = 0; k < z; k++){
                if(i==0||i==y-1||k==0||k==z-1||j==0||j==x-1){
                    aquario.dimensao[i].grid[j][k].ocupante[0] = new Posicionavel('r');
                    //printf("i %d j %d k % d \n", i,j,k);
                    aquario.dimensao[i].grid[j][k].ocupante[1] = NULL;
                } else {
                    aquario.dimensao[i].grid[j][k].ocupante[0] = NULL;
                    aquario.dimensao[i].grid[j][k].ocupante[1] = NULL;
                }
            }
        }
    }
}
cubo Ecossistema::aquario;
