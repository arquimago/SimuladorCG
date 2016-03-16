#include "Ecossistema.h"
#include <stdlib.h>
#include <time.h>

///POSICIONAVEL
posicao Posicionavel::getPosicao()
{return this->localizacao;}

void Posicionavel::setPosicao(posicao posicaoNova, int i)
{
    //seta posicao atual no cubo para nulo
    Ecossistema::ocupar(localizacao.x,localizacao.y,localizacao.z,i,NULL);
    //altera posicao atual
    this->localizacao.x = posicaoNova.x;
    this->localizacao.y = posicaoNova.y;
    this->localizacao.z = posicaoNova.z;
    //seta nova posicao no cubo
    Ecossistema::ocupar(localizacao.x,localizacao.y,localizacao.z,i,this);
}

void Posicionavel::agir()
{} //sobrecarregar

///PEIXE
int Peixe::getTaxa()
{return this->taxa;}

posicao Peixe::getDirecao()
{return this->direcao;}

int Peixe::getMassa()
{return this->massa;}

void Peixe::virar()
{
    srand(time(NULL));
    posicao direcaoNova;
    //seta direcoes aleatorias entre -1,0,1
    this->direcao.x=(rand() % 3) -1;
    this->direcao.y=(rand() % 3) -1;
    this->direcao.z=(rand() % 3) -1;
}

void Peixe::agir()
{
    this->fome();

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

void Peixe::morrer()
{
    //limbo (região dos mortos)
    posicao limbo;
    limbo.x,limbo.y,limbo.z = 0;
    this->setPosicao(limbo,1);
}

void Peixe::fome()
{
    this->diminuir(this->getTaxa());
}

void Peixe::diminuir(int massaPerdida)
{
    if (massaPerdida < this->getMassa())
        this->massa = this->getMassa() - massaPerdida;
    else
        this->morrer();
}

int Peixe::sangrar()
{
    this->diminuir(0);
    this->morrer();
    return this->getMassa();
}

Posicionavel** Peixe::verAFrente()
{
    //se tem planta/peixe/ retorna referencia
    //vazio retorna nulo
    //se for parede retorna pedra
}

///PLANTA
int Planta::getTaxa()
{return this->taxa;}

int Planta::getMassa()
{return this->massa;}

int Planta::sangrar()
{
    int massaAtual = this->getMassa();
    this->diminuir(75);
    //diminui massa
    if (massaAtual >= 75)
        return 75;
    else
        //retorna a quantidade restante da massa
        return abs(massaAtual - 75);
}

void Planta::diminuir(int massaPerdida)
{
    if (massaPerdida < this->getMassa())
        this->massa = this->getMassa() - massaPerdida;
    else
        this->morrer();
}

void Planta::morrer ()
{
    //limbo (região dos mortos)
    posicao limbo;
    limbo.x,limbo.y,limbo.z = 0;
    this->setPosicao(limbo,1);
}

bool Planta::explodir()
{

}

void Planta::agir()
{this->crescer();}

void Planta::crescer()
{
    this->massa = this->getMassa() + this->taxa;
    if (this->getMassa() > 1000)
        this->explodir();
}

///Pedra
Pedra::Pedra()
{

}

void Pedra::posicionar()
{

}
