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
	private:
		posicao localizacao;
		void posicionar ();
        	//codigo para gerar uma posicao aleatoria x y z
        	//checar em Cubo se a posicao esta ocupada ou nao.
        	//pedra e planta sobrecarregam essa fun��o, pois tem propriedades especiais para ela.
	public:
		posicao getPosicao();
		void setPosicao(posicao posicaoNova, int i);
		void agir();
		//planta e peixe vão sobrescrever esse metodo
};


class SerVivo: public Posicionavel
//pedra planta e peixe herdam dessa classe.
{
	private:
		int massa;
        	int taxa;

	public:
		SerVivo(int massa,int taxa);
		//seta massa e taxa iniciais
        	int getTaxa();
		int getMassa();
		void setMassa(int massa);
       		void explodir(int ser);
        	//chama a fun��o morrer e aloca varios peixes menores no Cubo
		void diminuir(int qtd, int ser);
		// diminui massa em i pontos por fome/mordida. se a massa chegar a 0, chama a fun��o morrer
		void morrer(int ser);
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
		Peixe(int taxa);
		//construtor. seta os valores iniciais de massa e dire��o (aleatoria). chama metodo posicionar.
	        //chama construtor de serVivo, passando a massa e taxa
	        void agir();
	        //chama função fome
	        //usa ve a frente, muda direção de peixe
	        //se encontrar planta morde
		//se encontrar peixe e for maior, come
		//se encontrar peixe e for menor, morre
        	posicao getDirecao();
		void fome();
		//chama a fun��o privada diminuir com a taxa de diminuição
		void morder(Posicionavel*);
		// come planta/peixe e almenta a massa.  checa para ver se nao � uma pedra.
		//chama a funcao privada explodir caso a massa ultrapasse do limite
		//checar se massa do peixe � maior.
		//chama metodo sangrar do mordido.
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
		void posicionar();
		//pedra e planta sempre sao alocadas no ch�o
		//planta nao acumula em cima de outras
	public:

		Planta(int taxa);//construtor. chama metodo posicionar. seta valores iniciais de massa.
        	//chama construtor de serVivo, passando a massa e taxa
		int sangrar(); //ocorre ao ser mordido. chama a fun��o privada diminuir, recebe a massa retornada
		//retorna a quantidade que "sangrou"
        	void agir(); //chama metodo crescer
};

class Pedra: public Posicionavel
{
	private:
		void posicionar(int x,int y,int z);
        	//pedra e planta sempre sao alocadas no ch�o
        	//pedra acumula em cima das outras
	public:
		Pedra();//construtor. chama metodo posicionar.
};




#endif // POSICIONAVEL_H


