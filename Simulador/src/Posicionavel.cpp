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
    Pedra* pedra = (Pedra*) proximo[0];

    while (pedra != NULL)
    {
        //enquanto houver pedra
        //mudar de direção até achar direção viavel
        this->virar();
        Posicionavel** proximo = this->verAFrente();
        pedra = (Pedra*) proximo[0];
    }
    Planta* planta = (Planta*) proximo[1];
    Peixe* peixe = (Peixe*)proximo[2];

    //não é pedra
    this->nadar();

    if (peixe != NULL)
    {
        //tem peixe
        //testes das massas

        if (peixe->getMassa() >= this->getMassa())
            peixe->morder(this);
        else
            this->morder(peixe);

    }
    else if (planta != NULL)
        //nao tem peixe mas tem planta
        this->morder(planta);
}

int Peixe::getMassa()
{
    return this->massa;
}

void Peixe::nadar()
{
    posicao direcaoAtual = this->getDirecao();
    posicao posicaoAtual = this->getPosicao();
    posicao proximaPosicao;

    proximaPosicao.x = posicaoAtual.x + direcaoAtual.x;
    proximaPosicao.y = posicaoAtual.y + direcaoAtual.y;
    proximaPosicao.z = posicaoAtual.z + posicaoAtual.z;

    this->setPosicao(proximaPosicao,2);
}

void Peixe::morder(Posicionavel* alvo)
{

}

int Peixe::sangrar()
{

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
