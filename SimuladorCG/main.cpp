#include "Ecossistema.h"
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



    //inicializar cubo
    //inicializar posicoes de pedras, plantas e peixes
    Ecossistema::inicializar(comprimento,largura,altura);
    //posicionar plantas pedras e peixes
    for (int i=0 ; i < qtdPedra ; i++) new Pedra();
    for (int i=0 ; i < qtdPlanta ; i++) new Planta(taxaCrescimentoPlanta);
    for (int i=0 ; i < qtdPeixe ; i++) new Peixe(taxaDiminuicaoPeixe);

    //programa rodando
    while(true)
    {
        draw(Ecossistema::Cubo);//projeto opengl para desenhar

        for (int k=0; k<altura; k++)
        {
            for (int j=0; j<largura; j++)
            {
                for (int i=0; i<comprimento; i++)
                {
                    Posicionavel ocupante** = Ecossistema::identificarOcupantes(i,j,k);
                    for (int pos = 0; pos < 2 ; pos++)
                    {
                        if (ocupante[pos] ==NULL)
                            break;
                        if (ocupante[pos].getTipo() == 'p') //SE FOR PLANTA, CRESCE
                            ocupante[pos].crescer();
                        else if (ocupante[pos].getTipo() == 'f') //SE FOR peixe
                        {
                            Posicionavel** proximo = ocupante[pos].verAFrente();
                            if (proximo != NULL)
                            {
                                while (proximo.getTipo() == 'r') //enquanto houver pedra
                                    peixes[pos].setDirecao();
                                    //mudar de direção até achar direção viavel
                            }
                            //nadar, tretar com peixe e planta

                            if (proximo.getTipo() = 'f')
                            {
                                if (proximo.getMassa() > ocupante.getMassa())
                                {

                                }
                                if (proximo.getMassa() < ocupante.getMassa())
                                {

                                }
                                if (proximo.getMassa() == ocupante.getMassa())
                                {

                                }

                            }

                            if (proximo.getTipo() = 'p')
                            {
                                ocupante.morder
                                proximo.

                            }

                            ocupante[pos].nadar();
                        }
                    }
                    }
                }
            }
        }


    }


}
