
#include "Ecossistema.h"
#include "stddef.h"
#include "stdio.h"

void Ecossistema::inicializar (int x, int y, int z)
{
    y+=2;
    x+=2;
    z+=2;

    aquario.dimensao = new plano[y];

    for(int iy = 0; iy < y; iy++){
        aquario.dimensao[iy].grid = new unidade*[x];
    }

    for(int iy = 0; iy < y; iy++) {
        for(int j = 0; j < x; j++){
            aquario.dimensao[iy].grid[j] = new unidade[z];
        }
    }

    for(int iy = 0; iy < y; iy++){
        for(int j = 0; j < x; j++){
            for(int k = 0; k < z; k++){
                if(iy==0||iy==y-1||k==0||k==z-1||j==0||j==x-1){
                    Ecossistema::ocupar(j,iy,k,0,new Posicionavel('r'));
                    Ecossistema::ocupar(j,iy,k,1,NULL);
                } else {
                    Ecossistema::ocupar(j,iy,k,0,NULL);
                    Ecossistema::ocupar(j,iy,k,1,NULL);
                }
            }
        }
    }
}
cubo Ecossistema::aquario;

Posicionavel** Ecossistema::identificarOcupantes (int x, int y, int z)
{
   Posicionavel** ocupantes = new Posicionavel*[2];
   ocupantes[0]==aquario.dimensao[y].grid[x][z].ocupante[0];
   ocupantes[1]==aquario.dimensao[y].grid[x][z].ocupante[0];

   return ocupantes;

}

void Ecossistema::ocupar (int x, int y, int z,int i, Posicionavel* corpo)
{
    aquario.dimensao[y].grid[x][z].ocupante[i] = corpo;
}
  
