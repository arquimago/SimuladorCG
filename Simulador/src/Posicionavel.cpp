#include "Ecossistema.h"
#include <stdlib.h>
#include <time.h>

Posicionavel::Posicionavel(char c)
{
   this->tipo= c;//ctor
}

char Posicionavel::getTipo()
{
   return this->tipo;
}

posicao Posicionavel::getPosicao()
{
    return this->localizacao;
}

void Posicionavel::setPosicao(posicao posicaoNova, int i)
{
    this->localizacao.x = posicaoNova.x;
    this->localizacao.y = posicaoNova.y;
    this->localizacao.z = posicaoNova.z;

    Ecossistema::ocupar(localizacao.x,localizacao.y,localizacao.z,i,this);

}

void Posicionavel::agir()
{
    //faz nada

}
//PEIXE

void Peixe::virar()
{
    srand(time(NULL));
    posicao direcaoNova;

    this->direcao.x=(rand() % 3) -1;
    this->direcao.y=(rand() % 3) -1;
    this->direcao.z=(rand() % 3) -1;
}

posicao Peixe::getDirecao()
{
    return this->direcao;
}

void Peixe::agir()
{
    Posicionavel** proximo = this->verAFrente();
    if (proximo[0] != NULL)
    {
        int tentativas = 1;

        while (proximo[0]->getTipo() == 'r' ||
              (proximo[0]->getTipo() == 'r' && proximo[1]->getTipo() == 'p'))
        //enquanto houver pedra ou terreno totalmente ocupado
        //mudar de direção até achar direção viavel
        //ou ate tentar todas as direcoes
        {
            if (tentativas == 10)
                return; //não consegue se mover.
            this->virar();
            Posicionavel** proximo = this->verAFrente();

            tentativas++;
        }
    }




    //condiç~eos abaixo pra testar [0] e [1]
    /*

    this->nadar(); ///qual i???
    if (proximo.getTipo() = 'f')
    {
        if (proximo.getMassa() >= this->getMassa())
            proximo.morder(this);
        else
            ocupante.morder(proximo);
    }

    if (proximo.getTipo() = 'p')
        ocupante.morder(proximo);
    */

}

void Peixe::nadar(int i)
{
    posicao direcaoAtual = this->getDirecao();
    posicao posicaoAtual = this->getPosicao();
    posicao proximaPosicao;

    proximaPosicao.x = posicaoAtual.x + direcaoAtual.x;
    proximaPosicao.y = posicaoAtual.y + direcaoAtual.y;
    proximaPosicao.z = posicaoAtual.z + posicaoAtual.z;

    this->setPosicao(proximaPosicao,i);
}

void Peixe::morder(Posicionavel* alvo)
{
    //avan�a 1 unidade na dire��o.
}


Posicionavel** Peixe::verAFrente()
{
            //se tem planta/peixe/ retorna referencia
        //vazio retorna nulo
        //se for parede retorna pedra
}

//PLANTA

int Planta::sangrar()
{

    return this->diminuir(75);
}

int Planta::diminuir(int massaPerdida)
{

    if (massaPerdida < this->massa)
    {
        this->massa = this->massa - massaPerdida;
        return massaPerdida;
    }
    else
    {
        this->morrer();
        return this->massa;
    }
}

void Planta::morrer ()
{

}

bool Planta::explodir()
{

}

void Planta::agir()
{
    this->crescer();
}

void Planta::crescer()
{
    this->massa = this->massa + this->taxa;
    if (this->massa > 1000)
        this->explodir();
}
