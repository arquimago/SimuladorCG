#include "Ecossistema.h"
#include "stddef.h"
#include "stdio.h"

cubo Ecossistema::aquario;
posicao Ecossistema::limites;

void Ecossistema::inicializar (int x, int y, int z)
{
    limites.x = x;
    limites.y = y;
    limites.z = z;
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
    //seta tudo como null
    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < x; j++)
        {
            for(int k = 0; k < z; k++)
            {
                    Ecossistema::ocupar(j,i,k,0,NULL);
                    Ecossistema::ocupar(j,i,k,1,NULL);
                    Ecossistema::ocupar(j,i,k,2,NULL);
            }
        }
    }

    Pedra* pedra = new Pedra();
    //cria uma nova pedra que cai até o fundo
    //cria as paredes do cubo de pedra
    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < x; j++)
        {
            for(int k = 0; k < z; k++)
            {
                if(i==0||i==y-1||k==0||k==z-1||j==0||j==x-1)
                {
                    Ecossistema::ocupar(j,i,k,0,pedra);
                }
            }
        }
    }
}

Posicionavel** Ecossistema::identificarOcupantes (int x, int y, int z)
{	//printf("Ocupantes da posicao %d %d %d\n",x,y,z);
	if (x<0 || y < 0 || z < 0)
		printf("-------------------BUSCANDO LIMITE INFERIOR\n");
	if (x>6 || y > 5 || z > 8)
		printf(" ------------------BUSCANDO LIMITE SUPERIOR\n");		
	return aquario.dimensao[y].grid[x][z].ocupante;
}

void Ecossistema::ocupar (int x, int y, int z,int i, Posicionavel* corpo)
{	
	aquario.dimensao[y].grid[x][z].ocupante[i] = corpo;
}

posicao* Ecossistema::getLimites()
{return &limites;}
