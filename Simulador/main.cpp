#include "Ecossistema.h"
#include "stdio.h"
#include "Posicionavel.h"
#include "Desenho.h"

int main ()
{

    //ler arquivo de beatriz

    int qtdPeixe = 3;
    int qtdPedra = 20;
    int qtdPlanta = 4;
    int altura = 3;  //y
    int largura = 6; //z
    int comprimento = 4;//x
    int taxaCrescimentoPlanta = 15;
    int taxaDiminuicaoPeixe = 10;

    Desenho ringue;



    //inicializar cubo
    //inicializar posicoes de pedras, plantas e peixes
    Ecossistema::inicializar(comprimento,altura,largura);

    /* //IMPRESSAO DO INICIALIZAR

         for(int i = 0; i < altura+2; i++){
            for(int j = 0; j < comprimento+2; j++){
                for(int k = 0; k < largura+2; k++){
                   //printf("X = %d Y = %d Z=%d ", j, i, k);
                   if(Ecossistema::aquario.dimensao[i].grid[j][k].ocupante[0]!=NULL){
                        printf("%c ", Ecossistema::aquario.dimensao[i].grid[j][k].ocupante[0]->getTipo());
                   } else {
                        printf("w ");
                       // printf("%d ", j);
                   }
                }
                printf(" Quebrou linhaaaaaaa \n");
            }
            printf("Quebra ordinaria\n");
        }

    */

    //posicionar plantas pedras e peixes
    //
    for (int i=0 ; i < qtdPedra ; i++) new Pedra();
    for (int i=0 ; i < qtdPlanta ; i++) new Planta(taxaCrescimentoPlanta);
    for (int i=0 ; i < qtdPeixe ; i++) new Peixe(taxaDiminuicaoPeixe);

    //programa rodando
    /*
    while(true)
    {
        ringue.desenhar();
        for (int k=0; k<altura; k++)
        {
            for (int j=0; j<largura; j++)
            {
                for (int i=0; i<comprimento; i++)
                {
                    Posicionavel ocupante** = Ecossistema::identificarOcupantes(i,j,k);
                    for (int pos = 0, pos < 2, pos++)
                        if (ocupante[0] != NULL) //TEM ALGO
                            ocupante[pos]->agir();

                }
            }
        }
    }

    */
}


