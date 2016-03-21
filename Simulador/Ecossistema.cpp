#include "Ecossistema.h"
#include "stddef.h"
#include "stdio.h"

cubo Ecossistema::aquario;

void Ecossistema::inicializar (int x, int y, int z)
{
    y+=2;
    x+=2;
    z+=2;

    aquario.dimensao = new plano[y];

    for(int i = 0; i < y; i++)
    {
        aquario.dimensao[i].grid = new unidade*[x];
    }

    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < x; j++)
        {
            aquario.dimensao[i].grid[j] = new unidade[z];
        }
    }

    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < x; j++)
        {
            for(int k = 0; k < z; k++)
            {
                if(i==0||i==y-1||k==0||k==z-1||j==0||j==x-1)
                {
                    Ecossistema::ocupar(j,i,k,0,new Pedra());
                    Ecossistema::ocupar(j,i,k,1,NULL);
                    Ecossistema::ocupar(j,i,k,2,NULL);
                }
                else
                {
                    Ecossistema::ocupar(j,i,k,0,NULL);
                    Ecossistema::ocupar(j,i,k,1,NULL);
                    Ecossistema::ocupar(j,i,k,2,NULL);
                }
            }
        }
    }
}

Posicionavel** Ecossistema::identificarOcupantes (int x, int y, int z)
{
   Posicionavel** ocupantes = new Posicionavel*[2];
   ocupantes[0]==aquario.dimensao[y].grid[x][z].ocupante[0];
   ocupantes[1]==aquario.dimensao[y].grid[x][z].ocupante[1];
   ocupantes[2]==aquario.dimensao[y].grid[x][z].ocupante[2];

   return ocupantes;

}

void Ecossistema::ocupar (int x, int y, int z,int i, Posicionavel* corpo)
{
    aquario.dimensao[y].grid[x][z].ocupante[i] = corpo;
}
