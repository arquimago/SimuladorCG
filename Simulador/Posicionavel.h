#ifndef POSICIONAVEL_H
#define POSICIONAVEL_H

// usado para posicao e direcao.
//direcao � +1, 0 ou -1 em cada um dos eixos, n�o podendo ser 0 nos tr�s
typedef struct {
	int x;
	int y;
	int z;
} posicao;

class Posicionavel
//pedra planta e peixe herdam dessa classe.
{
	protected:
		posicao localizacao;
		int id; //identificador de posicionavel
		void posicionar();
		//peixe e planta tem a mesma função, pedra sobrecarrega
        //codigo para gerar uma posicao aleatoria x y z
        //checar em Cubo se a posicao esta ocupada ou nao.

	public:
		posicao* getPosicao();
		Posicionavel(int id);
		//seta id
		int getId();
		void setPosicao(int x,int y, int z);
		void agir();
		//planta e peixe vão sobrescrever esse metodo
};


class SerVivo: public Posicionavel
//pedra planta e peixe herdam dessa classe.
{
	protected:
		int massa;
		int limite;
        int taxa;
		bool agiu;

		void setMassa(int massa);
	public:
		SerVivo(int massa,int taxa,int limite,int id);
		//passa id para classe pai
		//seta massa e taxa iniciais e limites iniciais
        int getTaxa();
		int getMassa();
		bool getAgiu();
		void setAgiu();
        void explodir();
        //chama a fun��o morrer e aloca varios peixes menores no Cubo
		void diminuir(int qtd);
		// diminui massa em qtd pontos por fome/mordida. se a massa chegar a 0, chama a fun��o morrer
		void aumentar(int qtd);
		// aumenta massa em qtd pontos por fome/mordida. se a massa chegar a maximo, chama a fun��o explodir
		void morrer();
		//tira referencia no cubo e coloca na posicao do limbo, 0,0,0
		int sangrar();
		//limpa sua posicao no Cubo (seta para 0,0,0,2)

};



class Peixe: public SerVivo
{
	private:
		posicao direcao;
        void nadar();
		//avan�a 1 unidade na dire��o.
        Posicionavel** verAFrente();
        //se tem planta/peixe/ retorna referencia
        //vazio retorna nulo
        //se for parede retorna pedra
        void virar();
        //muda aleatoriamente sua dire��o. testar para nao ficar de cabe�a para baixo
	public:
		Peixe(int taxaInicial, int x, int y, int z, int massa);  //construtor da explosão
		Peixe(int taxaInicial);
		//construtor. seta os valores iniciais de massa e dire��o (aleatoria). chama metodo posicionar.
        //chama construtor de serVivo, passando a massa e taxa e 1500 como limite
        void agir();
        //chama função fome
        //usa ve a frente, muda direção de peixe
        //se encontrar planta morde
		//se encontrar peixe e for maior, come
		//se encontrar peixe e for menor, morre
        posicao* getDirecao();
		void fome();
		//chama a fun��o privada diminuir com a taxa de diminuição
		void morder(Posicionavel*);
		//chama metodo crescer do peixe de acordo com o retorno de sangrar do mordido
		int sangrar();
		//essa fun��o chama a fun��o morrer.
		//retorna toda a massa do peixe

};

class Planta: public SerVivo
{
	private:
		void crescer();
		//aumenta massa e chama a fun��o privada diminuir e explodir caso passe do limite
	public:
		Planta(int taxaInicial, int x, int y, int z, int massa);  //construtor da explosão
		Planta(int taxaInicial);
		//construtor. chama metodo posicionar.
        //chama construtor de serVivo, passando a massa e taxa, e 1000 como limite
        //passa id para construtor de serVivo
		int sangrar(); //ocorre ao ser mordido. chama a fun��o privada diminuir, recebe a massa retornada
		//retorna a quantidade que "sangrou"
        void agir(); //chama metodo crescer
};

class Pedra: public Posicionavel
{
	private:
		void posicionar();
        //pedra e planta sempre sao alocadas no ch�o
        //pedra acumula em cima das outras
	public:
		Pedra();//construtor. chama metodo posicionar.
};




#endif // POSICIONAVEL_H


