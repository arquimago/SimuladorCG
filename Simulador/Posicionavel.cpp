#include "Ecossistema.h"
#include <stdlib.h>
#include "stdio.h"
#include <ctime>

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
    
	int i = 0;
    posicao* limites = Ecossistema::getLimites();
    do{
        i++;
		sorteio_x = (rand() % limites->x) + 1;
		sorteio_y = (rand() % limites->y) + 1;
        sorteio_z = (rand() % limites->z) + 1;
    } while(Ecossistema::identificarOcupantes(sorteio_x, sorteio_y, sorteio_z)[0]!=NULL ||
	Ecossistema::identificarOcupantes(sorteio_x, sorteio_y, sorteio_z)[this->getId()]!=NULL);
    setPosicao(sorteio_x,sorteio_y,sorteio_z);
}

///SERVIVO
void SerVivo::explodir(){
	
	int id = this->getId();//1 planta, 2 peixe
	int numero_filhotes=0;
	int massa_filhotes=0;
	posicao* posicao_pai = this->getPosicao();

	//if(id == 1) numero_filhotes = rand()%15+12;
	//else numero_filhotes = rand()%14+13;
	
	if(id == 1) numero_filhotes = rand()%8+2;
	else numero_filhotes = rand()%7+2;
	
	posicao pai;
	pai.x = (posicao_pai->x);
	pai.y = (posicao_pai->y);
	pai.z = (posicao_pai->z);
	
	this->morrer();
	
	massa_filhotes = (this->getMassa())/numero_filhotes;
	int pos_x,pos_y,pos_z;
	int total_vagas = 0;
	bool filhotes[3][3][3];//se tiver vaga recebe true, senão recebe false
	
	for(int i = 0;i < 3;i++){
		for(int j = 0;j < 3;j++){
			for(int k = 0;k < 3;k++){
                posicao filho;
				filho.x = (pai.x)+i-1;
				filho.y = (pai.y)+j-1;
				filho.z = (pai.z)+k-1;
				Posicionavel** ocupante = Ecossistema::identificarOcupantes(filho.x,filho.y,filho.z);
				if((i==1&&j==1&&k==1&&id==2)||ocupante[0]!=NULL){
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
            new Planta(this->getTaxa(),pai.x+pos_x-1, pai.y+pos_y-1, pai.z+pos_z-1, massa_filhotes);
		else
		    new Peixe(this->getTaxa(), pai.x+pos_x-1, pai.y+pos_y-1, pai.z+pos_z-1, massa_filhotes);
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
	this->agiu = false;
}

int SerVivo::sangrar()
{} //sobrecarregavel

bool SerVivo::getAgiu(){
	return this->agiu;
}

void SerVivo::setAgiu(){
	this->agiu = !this->agiu;
}

void SerVivo::morrer()
{
	this->setPosicao(0,0,0);
}

void SerVivo::diminuir(int massaPerdida)
{
	if (massaPerdida < this->massa){
		this->massa -= massaPerdida;
	}
    else {
		this->morrer();
	}
}

bool SerVivo::aumentar(int massaGanha)
{
   bool explodiu = false;
   this->massa += massaGanha;
   if (this->massa > this->limite){
		this->explodir();
		explodiu = true;
   }
   return explodiu;
}

///PEIXE

posicao* Peixe::getDirecao()
{return &this->direcao;}

void Peixe::virar()
{
	printf("peixe virando");
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
    printf("peixe virou");
}

void Peixe::agir()
{
	printf("peixe agindo");
	bool explodiu = false;
	this->setAgiu();
    Posicionavel** proximo = this->verAFrente();
	
	//Problema no funcionamento aqui dentro, as vezes dá loop infinito
	while (proximo[0]!=NULL)
    {
        //enquanto houver pedra
        //mudar de direção até achar direção viavel
        this->virar();
        proximo = this->verAFrente();
    }
	
    //não é pedra
	
    if (proximo[2] != NULL)
    {
		//tem peixe
        //testes das massas
        if (((Peixe*) proximo[2])->getMassa() >= this->getMassa()){
			((Peixe*) proximo[2])->morder(this);
			printf("peixe parando de agir porque foi mordido");
			return;
		} else{
			explodiu = this->morder(((Peixe*) proximo[2]));
		}
    } else if (((Planta*) proximo[1]) != NULL){
		//nao tem peixe mas tem planta
		explodiu = this->morder(((Planta*) proximo[1]));
	}
	
	if (!explodiu){
		this->nadar();
		this->fome();
	}	
	printf("peixe agiu");
}

void Peixe::nadar()
{
	printf("peixe nadando");
    posicao* direcaoAtual = this->getDirecao();
    posicao* posicaoAtual = this->getPosicao();
    posicao proximaPosicao;

    proximaPosicao.x = posicaoAtual->x + direcaoAtual->x;
    proximaPosicao.y = posicaoAtual->y + direcaoAtual->y;
    proximaPosicao.z = posicaoAtual->z + direcaoAtual->z;
    
	this->setPosicao(proximaPosicao.x,proximaPosicao.y,proximaPosicao.z);
	printf("peixe nadou");
}

bool Peixe::morder(Posicionavel* alvo)
{
	printf("peixe mordendo");
    int m;
	SerVivo* ser = (SerVivo*) alvo;
	if(ser->getId()==1){
		m = ((Planta*) ser)->sangrar();
	}else{
		m = ((Peixe*) ser)->sangrar();
	}
	printf("peixe mordeu");
	return this->aumentar(m);
}

void Peixe::fome()
{
	printf("inicio de fome de peixe");
	this->diminuir(this->getTaxa());
	printf("fim de fome de peixe");
}

int Peixe::sangrar()
{
	printf("peixe sangrando");
    int massa = this->getMassa();
    this->diminuir(massa);
    printf("peixe sangrou");
    return massa;
}

Posicionavel** Peixe::verAFrente()
{
	printf("peixe vendo a frente");
	posicao* direcaoAtual = this->getDirecao();
    posicao* posicaoAtual = this->getPosicao();
    posicao proximaPosicao;
	
    proximaPosicao.x = posicaoAtual->x + direcaoAtual->x;
    proximaPosicao.y = posicaoAtual->y + direcaoAtual->y;
    proximaPosicao.z = posicaoAtual->z + direcaoAtual->z;
printf("peixe viu a frente");
    return Ecossistema::identificarOcupantes(proximaPosicao.x,proximaPosicao.y,proximaPosicao.z);
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
	printf("novo peixe de explosão nascendo");
	Posicionavel** ocupante = Ecossistema::identificarOcupantes(x,y,z);
    
	if(ocupante[2]!= NULL) //há peixe
	{
		//testes das massas
        if (((Peixe*)ocupante[2])->getMassa() >= this->getMassa()){
			((Peixe*)ocupante[2])->morder(this);
		}
        else{
			this->morder(((Peixe*)ocupante[2]));
		}   	
	}
	else //se nao tem, seta a posicao
	{
		this->virar();
        this->setPosicao(x,y,z);
	}
	printf("peixe de explosão nasceu");
}


///PLANTA


Planta::Planta(int taxaInicial):SerVivo(150,taxaInicial,1000,1)
{this->posicionar();}

Planta::Planta(int taxaInicial, int x, int y ,int z, int massa):SerVivo(massa,taxaInicial,1000,1)
{
	Posicionavel** ocupante = Ecossistema::identificarOcupantes(x,y,z);
	if(ocupante[1] != NULL) { //há planta, uma planta "come" a outra
		((Planta*)ocupante[1])->aumentar(massa);
	} 
	else { //se nao tem, seta a posicao
		this->setPosicao(x,y,z);
	}
}

int Planta::sangrar()
{
	int massaAtual = this->getMassa();
    this->diminuir(75);
    //diminui massa
    if (massaAtual >= 75){
		return 75;
	}else{
		//retorna a quantidade restante da massa
		return abs(massaAtual - 75);
	}	
}

void Planta::agir()
{	this->setAgiu();
	this->crescer();}

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

