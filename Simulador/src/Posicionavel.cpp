#include "Ecossistema.h"
#include <stdlib.h>
#include <time.h>

///POSICIONAVEL
posicao Posicionavel::getPosicao()
{return this->localizacao;}

int Posicionavel::getId()
{return this->id;}

Posicionavel::Posicionavel(int id)
{
    this->id = id;
}

void Posicionavel::setPosicao(int x, int y, int z)
{
    //seta posicao atual no cubo para nulo
    Ecossistema::ocupar(localizacao.x,localizacao.y, localizacao.z, this->getId(), NULL);
    //altera posicao atual
    this->localizacao.x = x;
    this->localizacao.y = y;
    this->localizacao.z = z;
    //seta nova posicao no cubo
    Ecossistema::ocupar(localizacao.x, localizacao.y, localizacao.z,this->getId(), this);
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

SerVivo::SerVivo(int massa,int taxa, int limite, int id):Posicionavel(id)
{
    this->massa = massa;
    this->taxa = taxa;
    this->limite = limite;
}

int SerVivo::sangrar()
{} //sobrecarregavel


void SerVivo::morrer()
{
    //limbo (região dos mortos)
    posicao limbo;
    limbo.x,limbo.y,limbo.z = 0;
    this->setPosicao(limbo);
}

void SerVivo::diminuir(int massaPerdida)
{
    if (massaPerdida < this->getMassa())
        this->massa = this->getMassa() - massaPerdida;
    else
        this->morrer();
}

void SerVivo::aumentar(int massaGanha)
{
   this->setMassa(this->getMassa() + massaGanha);
   if (this->getMassa() > this->limite)
        this->explodir();
}

void SerVivo::explodir()
{
    // usar this->getId();  para saber quem é  0,1,2
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
void Peixe::posicionar(){
	int sorteio_x, sorteio_z, sorteio_y;
    srand (time(NULL));
    do{
        sorteio_x = rand()%x+1;
		sorteio_y = rand()%y+1;
        sorteio_z = rand()%z+1;
    } while(aquario.identificarOcupantes(sorteio_x, sorteio_y, sorteio_z)[0]!=NULL &&
	aquario.identificarOcupantes(sorteio_x, sorteio_y, sorteio_z)[2]!=NULL);

    setPosicao(sorteio_x,sorteio_y,sorteio_z);
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

    this->setPosicao(proximaPosicao);
}

void Peixe::morder(Posicionavel* alvo)
{
    SerVivo* ser = (SerVivo*) alvo;
    this->aumentar(ser->sangrar());
}

void Peixe::fome()
{this->diminuir(this->getTaxa());}

int Peixe::sangrar()
{
    int massa = this->getMassa();
    this->diminuir(0);
    this->morrer();
    return massa;
}

Posicionavel** Peixe::verAFrente()
{
    posicao direcaoAtual = this->getDirecao();
    posicao posicaoAtual = this->getPosicao();
    posicao proximaPosicao;

    proximaPosicao.x = posicaoAtual.x + direcaoAtual.x;
    proximaPosicao.y = posicaoAtual.y + direcaoAtual.y;
    proximaPosicao.z = posicaoAtual.z + posicaoAtual.z;

    return Ecossistema::identificarOcupantes(proximaPosicao.x,proximaPosicao.y,proximaPosicao.z);
}

Peixe::Peixe(int taxaInicial):SerVivo(100,taxaInicial,1000,2)
{this->posicionar();}

Peixe::Peixe(int taxaInicial, int x, int y ,int z, int massa):SerVivo(massa,taxaInicial,1000,2)
{
	Posicionavel ocupante** = Ecossistema::identificarOcupantes(x,y,z);
    	Peixe* peixe = (Peixe*)proximo[2];
	if(peixe != NULL) //há peixe
	{
		//testes das massas
        	if (peixe->getMassa() >= this->getMassa())
            		peixe->morder(this);
        	else
            		this->morder(peixe);
	}
	else //se nao tem, seta a posicao
		this->setPosicao(x,y,z);
}


///PLANTA


Planta::Planta(int taxaInicial):SerVivo(150,taxaInicial,1000,1)
{this->posicionar();}

Planta::Planta(int taxaInicial, int x, int y ,int z, int massa):SerVivo(massa,taxaInicial,1000,1)
{
	Posicionavel ocupante** = Ecossistema::identificarOcupantes(x,y,z);
    	Planta* planta = (Planta*)proximo[1];
	if(planta != NULL) //há planta, uma planta "come" a outra
		planta->aumentar(massa);
	else //se nao tem, seta a posicao
		this->setPosicao(x,y,z);
}


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

void Planta::agir()
{this->crescer();}

void Planta::crescer()
{this->aumentar(this->getTaxa());}

void Planta::posicionar(){
	int sorteio_x, sorteio_z, sorteio_y;
    srand (time(NULL));
    do{
        sorteio_x = rand()%x+1;
		sorteio_y = rand()%y+1;
        sorteio_z = rand()%z+1;
    } while(aquario.identificarOcupantes(sorteio_x, sorteio_y, sorteio_z)[0]!=NULL &&
	aquario.identificarOcupantes(sorteio_x, sorteio_y, sorteio_z)[1]!=NULL);

    setPosicao(sorteio_x,sorteio_y,sorteio_z);

}



///Pedra
Pedra::Pedra():Posicionavel(0)
{this->posicionar();}



void Pedra::posicionar()
{
    int sorteio_x, sorteio_z;
    int sorteio_y = 1;
    srand (time(NULL));
    do{
        sorteio_x = rand()%x+1;
        sorteio_z = rand()%z+1;
    } while(aquario.identificarOcupantes(sorteio_x, y, sorteio_z)[0]!=NULL);
    
	while(aquario.identificarOcupantes(sorteio_x, sorteio_y, sorteio_z)[0]!=NULL){
        sorteio_y++;
    }
    setPosicao(sorteio_x,sorteio_y,sorteio_z);
}




/*
void Pedra::posicionar()
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
*/
