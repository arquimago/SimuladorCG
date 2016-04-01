#ifndef POSICIONAVEL_H
#define POSICIONAVEL_H

// usado para posicao e direcao.
//direcao +1, 0 ou -1 em cada um dos eixos, nao podendo ser 0 nos tres
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
		//codigo para gerar uma posicao aleatoria x y z e alocar posicionavel no cubo
		//peixe e planta tem a mesma função, pedra sobrecarrega esta

	public:
		posicao* getPosicao();
		void setPosicao(int x,int y, int z);
		int getId();	
		Posicionavel(int id);
		//construtor
		//seta id

};


class SerVivo: public Posicionavel
//pedra planta e peixe herdam dessa classe.
{
	protected:
		int massa; //massa do ser
		int limite; //limite de massa
        int taxa; //taxa de crescimento/decrescimento
		bool agiu; //marca se agiu nesse turno


	public:
		SerVivo(int massa,int taxa,int limite,int id);
		//passa id para classe posicionavel
		//seta massa, taxa iniciais e limites iniciais
        int getTaxa();
		int getMassa();
		void setMassa(int massa);
		bool getAgiu();
		void setAgiu();
        void explodir();
        //chama a funcao morrer e aloca varios peixes menores no Cubo
		void diminuir(int qtd);
		// diminui massa em qtd pontos por fome/mordida. se a massa chegar a 0, chama a funcaoo morrer
		bool aumentar(int qtd);
		// aumenta massa em qtd pontos por fome/mordida. se a massa chegar a maximo, chama a funcaoo explodir
		//retorna true caso exploda
		void morrer();
		//tira referencia no cubo e coloca na posicao do limbo, 0,0,0
		int sangrar();
		//limpa sua posicao no Cubo (seta para 0,0,0,id)
		void agir();
		//sobrecarregada por peixe e planta
};



class Peixe: public SerVivo
{
	protected:
		posicao direcao; //direcao do peixe
        void nadar();
		//avanca 1 unidade na direcao.
        Posicionavel** verAFrente();
		//retorna quem está na proxima posicao (considerando a direcao)
        void virar();
        //muda aleatoriamente sua direco
	public:
		Peixe(int taxaInicial, int x, int y, int z, int massa);  
		//construtor da explosão, seta peixe em x y z
		Peixe(int taxaInicial);
		//construtor. seta os valores iniciais de massa e direco (aleatoria). chama metodo posicionar.
        //chama construtor de serVivo, passando a massa e taxa e 1500 como limite
        void agir();
		//acoes do peixe
        //chama função fome
        //usa ve a frente, muda direção de peixe
        //se encontrar planta morde
		//se encontrar peixe e for maior, come
		//se encontrar peixe e for menor, morre
		//finaliza a execucao desse metodo caso o peixe morra (por mordida ou explosao)
		//chama nadar
        posicao* getDirecao();
		void fome();
		//chama a funcao diminuir com a taxa de diminuição
		bool morder(Posicionavel*);
		//chama metodo aumentar  de SerVivo de acordo com o retorno de sangrar do mordido
		//retorna true caso exploda
		int sangrar();
		//essa funcao chama a funcao morrer.
		//retorna toda a massa do peixe

};

class Planta: public SerVivo
{
	private:
		void crescer();
		//chama funcao aumentar de acordo com a taxa de crescimento
	public:
		Planta(int taxaInicial, int x, int y, int z, int massa); 
		//construtor da explosão seta planta em x y z
		Planta(int taxaInicial);
		//construtor. chama metodo posicionar.
        //chama construtor de serVivo, passando a massa e taxa, e 1000 como limite
        //passa id para construtor de serVivo
		int sangrar(); 
		//ocorre ao ser mordido. chama a funco privada diminuir, recebe a massa retornada
		//retorna a quantidade que "sangrou"
        void agir(); 
		//acao da planta
		//chama metodo crescer
};

class Pedra: public Posicionavel
{
	private:
		void posicionar();
        //pedras são sempre alocadas no chao
        //pedra acumula em cima das outras
	public:
		Pedra();
		//construtor. chama metodo posicionar.
};




#endif // POSICIONAVEL_H


