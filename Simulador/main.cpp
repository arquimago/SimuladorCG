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
    int altura = 3;  //y     0  2
    int largura = 6; //z  0  5
    int comprimento = 4;//x 0 3
    int taxaCrescimentoPlanta = 15;
    int taxaDiminuicaoPeixe = 10;

    //inicializar cubo
    //inicializar posicoes de pedras, plantas e peixes
    Ecossistema::inicializar(comprimento,altura,largura);


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


