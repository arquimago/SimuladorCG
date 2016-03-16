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

///SERVIVO
int SerVivo::getTaxa()
{return this->taxa;}

int SerVivo::getMassa()
{return this->massa;}

void SerVivo::setMassa(int massa)
{this->massa = massa;}

SerVivo::SerVivo(int massa,int taxa)
{
    this->massa = massa;
    this->taxa = taxa;
}


void SerVivo::morrer(int i)
{
    //limbo (região dos mortos)
    posicao limbo;
    limbo.x,limbo.y,limbo.z = 0;
    this->setPosicao(limbo,i);
}

void SerVivo::diminuir(int massaPerdida, int i)
{
    if (massaPerdida < this->getMassa())
        this->massa = this->getMassa() - massaPerdida;
    else
        this->morrer(i);
}

void SerVivo::aumentar(int massaGanha,int i)
{
   this->setMassa(this->getMassa() + massaGanha);
   if (this->getMassa() > this->limite)
        this->explodir(i);
}

void SerVivo::explodir(int i)
{

}
///PEIXE

posicao Peixe::getDirecao()
{return this->direcao;}

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
{this->aumentar(alvo->sangrar(),2);}

void Peixe::fome()
{this->diminuir(this->getTaxa(),2);}

int Peixe::sangrar()
{
    this->diminuir(0,2);
    this->morrer(2);
    return this->getMassa();
}

Posicionavel** Peixe::verAFrente()
{
    posicao proximaPosicao;
    
    proximaPosicao.x = posicaoAtual.x + direcaoAtual.x;
    proximaPosicao.y = posicaoAtual.y + direcaoAtual.y;
    proximaPosicao.z = posicaoAtual.z + posicaoAtual.z;
    
    return Ecossistema::identificarOcupantes(proximaPosicao.x,proximaPosicao.y,proximaPosicao.z);
}

///PLANTA

int Planta::sangrar()
{
    int massaAtual = this->getMassa();
    this->diminuir(75,1);
    //diminui massa
    if (massaAtual >= 75)
        return 75;
    else
        //retorna a quantidade restante da massa
        return abs(massaAtual - 75);
}

void Planta::agir()
{this->crescer();}

void Planta::crescer()
{
    this->aumentar()
    this->setMassa(this->getMassa() + this->getTaxa());
    if (this->getMassa() > 1000);
        this->explodir(1);

}

///Pedra
Pedra::Pedra()
{

}

void Pedra::posicionar(int x,int y,int z)
{
    int sorteio_x, sorteio_z;
    int sorteio_y = 1;

    srand (time(NULL));

    //tales, use o metodo identificarOcupantes de ecossistema.Cubo agora é privado.
    do{
        sorteio_x = rand()%x+1;
        sorteio_z = rand()%z+1;
    } while(Ecossistema::aquario.dimensao[y].grid[sorteio_x][sorteio_z].ocupante[0]!=NULL);

    while(Ecossistema::aquario.dimensao[sorteio_y].grid[sorteio_x][sorteio_z].ocupante[0]!=NULL){
        sorteio_y++;
    }
    Ecossistema::ocupar(sorteio_x,sorteio_y,sorteio_z,0,this);
}    
