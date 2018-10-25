#include "Ecossistema.h"
#include <stdlib.h>
#include <time.h>
#include "stdio.h"
///POSICIONAVEL
posicao* Posicionavel::getPosicao()
{return &this->localizacao;}

int Posicionavel::getId()
{return this->id;}

Posicionavel::Posicionavel(int id)
{
    this->id = id;
    this->localizacao.x = 0;
    this->localizacao.y = 0;
    this->localizacao.z = 0;
}

void Posicionavel::setPosicao(int x, int y, int z)
{
    //seta posicao atual no cubo para nulo
    if (localizacao.x != 0 && localizacao.y != 0 && localizacao.z != 0) //se não estiver na origem
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

void Posicionavel::posicionar()
{
    int sorteio_x, sorteio_z, sorteio_y;
    srand(rand());

    posicao* limites = Ecossistema::getLimites();
    do{
        sorteio_x = (rand() % limites->x) + 1;
		sorteio_y = (rand() % limites->y) + 1;
        sorteio_z = (rand() % limites->z) + 1;
    } while(Ecossistema::identificarOcupantes(sorteio_x, sorteio_y, sorteio_z)[0]!=NULL &&
	Ecossistema::identificarOcupantes(sorteio_x, sorteio_y, sorteio_z)[this->getId()]!=NULL);
    setPosicao(sorteio_x,sorteio_y,sorteio_z);
}

///SERVIVO
void SerVivo::explodir(){
	int id = this->getId();//1 planta, 2 peixe
	int numero_filhotes=0;
	int massa_filhotes=0;
	srand (time(NULL));
	posicao* posicao_pai = this->getPosicao();

	if(id == 1) numero_filhotes = rand()%15+12;
	else numero_filhotes = rand()%14+13;

    this->morrer();
	massa_filhotes = (this->getMassa())/numero_filhotes;
	int pos_x = -1;
	int pos_y = -1;
	int pos_z = -1;
	int total_vagas = 0;
	bool filhotes[3][3][3];//se tiver vaga recebe true, senão recebe false
	for(int i = 0;i < 3;i++){
		for(int j = 0;j < 3;j++){
			for(int k = 0;k < 3;k++){
                Posicionavel** pedra = Ecossistema::identificarOcupantes(posicao_pai->x+i-1,posicao_pai->y+j-1,posicao_pai->z+k-1);
				if((i==1&&j==1&&k==1&&id==2)||pedra!=NULL){
					filhotes[i][j][k] = false;
				} else {
					filhotes[i][j][k] = true;
					total_vagas++;
				}
			}
		}
	}
	if(total_vagas < numero_filhotes) numero_filhotes = total_vagas;
	//se tiver menos vagas que filhotes, reduzo o numero de filhotes pro total de vagas, senão o proximo loop poderia ser infinito
	//daria pra otimizar os sorteios com um vetor de ponteiros e tal, mas sem tempo pra otimizar agora.
	for(int i = 0; i < numero_filhotes; i++){
		do{
			pos_x = rand()%3;
			pos_y = rand()%3;
			pos_z = rand()%3;
		}while(!filhotes[pos_x][pos_y][pos_z]);

		if(id == 1)
            new Planta(this->getTaxa(),posicao_pai->x+pos_x-1, posicao_pai->y+pos_y-1, posicao_pai->z+pos_z-1, massa_filhotes);
		else
            new Peixe(this->getTaxa(),posicao_pai->x+pos_x-1, posicao_pai->y+pos_y-1, posicao_pai->z+pos_z-1, massa_filhotes);
		filhotes[pos_x][pos_y][pos_z] = false;
	}
}

int SerVivo::getTaxa()
{return this->taxa;}

void SerVivo::setMassa(int massa)
{this->massa = massa;}

int SerVivo::getMassa()
{return this->massa;}

SerVivo::SerVivo(int massa,int taxa, int limite, int id):Posicionavel(id)
{
    this->massa = massa;
    this->taxa = taxa;
    this->limite = limite;
}

int SerVivo::sangrar()
{} //sobrecarregavel


void SerVivo::morrer()
{this->setPosicao(0,0,0);}

void SerVivo::diminuir(int massaPerdida)
{
    if (massaPerdida < this->massa)
        this->massa = this->massa- massaPerdida;
    else
        this->morrer();
}

void SerVivo::aumentar(int massaGanha)
{
   this->massa = this->getMassa() + massaGanha;
   if (this->massa> this->limite)
        this->explodir();
}

///PEIXE

posicao* Peixe::getDirecao()
{return &this->direcao;}

void Peixe::virar()
{
    srand(time(NULL));
    //seta direcoes aleatorias entre -1,0,1
    int x = 0,y = 0,z = 0;
    while (x == 0 && y == 0 && z == 0) //enquanto não possuir uma direção
    {
        x = (rand() % 3) -1;
        y = (rand() % 3) -1;
        z = (rand() % 3) -1;
    }
    this->direcao.x= x;
    this->direcao.y= y;
    this->direcao.z= z;
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
    posicao* direcaoAtual = this->getDirecao();
    posicao* posicaoAtual = this->getPosicao();
    posicao* proximaPosicao;

    proximaPosicao->x = posicaoAtual->x + direcaoAtual->x;
    proximaPosicao->y = posicaoAtual->y + direcaoAtual->y;
    proximaPosicao->z = posicaoAtual->z + posicaoAtual->z;

    this->setPosicao(proximaPosicao->x,proximaPosicao->y,proximaPosicao->z);
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
    posicao* direcaoAtual = this->getDirecao();
    posicao* posicaoAtual = this->getPosicao();
    posicao* proximaPosicao;

    proximaPosicao->x = posicaoAtual->x + direcaoAtual->x;
    proximaPosicao->y = posicaoAtual->y + direcaoAtual->y;
    proximaPosicao->z = posicaoAtual->z + posicaoAtual->z;

    return Ecossistema::identificarOcupantes(proximaPosicao->x,proximaPosicao->y,proximaPosicao->z);
}

Peixe::Peixe(int taxaInicial):SerVivo(100,taxaInicial,1000,2)
{
    this->localizacao.x = 0;
    this->localizacao.y = 0;
    this->localizacao.z = 0;
    this->virar();
    this->posicionar();
}

Peixe::Peixe(int taxaInicial, int x, int y ,int z, int massa):SerVivo(massa,taxaInicial,1000,2)
{
	Posicionavel** ocupante = Ecossistema::identificarOcupantes(x,y,z);
    Peixe* peixe = (Peixe*)ocupante[2];
	if(peixe != NULL) //há peixe
	{
		//testes das massas
        	if (peixe->getMassa() >= this->getMassa())
            		peixe->morder(this);
        	else
            		this->morder(peixe);
	}
	else //se nao tem, seta a posicao
	{
        this->virar();
        this->setPosicao(x,y,z);
	}
}


///PLANTA


Planta::Planta(int taxaInicial):SerVivo(150,taxaInicial,1000,1)
{this->posicionar();}

Planta::Planta(int taxaInicial, int x, int y ,int z, int massa):SerVivo(massa,taxaInicial,1000,1)
{
	Posicionavel** ocupante = Ecossistema::identificarOcupantes(x,y,z);
    	Planta* planta = (Planta*)ocupante[1];
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


///Pedra
Pedra::Pedra():Posicionavel(0)
{this->posicionar();}



void Pedra::posicionar()
{
    int sorteio_x, sorteio_z;
    int sorteio_y = 0;
    posicao* limites = Ecossistema::getLimites();
    srand(rand());
    Posicionavel** ocupante;
    do{
        sorteio_x = (rand()%limites->x) + 1;
        sorteio_z = (rand()%limites->z) + 1;

        ocupante = Ecossistema::identificarOcupantes(sorteio_x, limites->y, sorteio_z);
    } while(ocupante[0]!= NULL);

    ocupante = Ecossistema::identificarOcupantes(sorteio_x, sorteio_y, sorteio_z);
    while(ocupante[0]!=NULL){
        sorteio_y++;
        ocupante = Ecossistema::identificarOcupantes(sorteio_x, sorteio_y, sorteio_z);
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
