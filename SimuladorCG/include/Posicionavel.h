#ifndef POSICIONAVEL_H
#define POSICIONAVEL_H

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
// usado para posicao e direcao.
//direcao é +1, 0 ou -1 em cada um dos eixos, não podendo ser 0 nos três
typedef struct {
	int x;
	int y;
	int z;
} posicao;


class Posicionavel //pedra planta e peixe herdam dessa classe.
{
	private:

		posicao localizacao;

		void posicionar ();
        //codigo para gerar uma posicao aleatoria x y z
        //checar em Cubo se a posicao esta ocupada ou nao.
        //pedra e planta sobrecarregam essa função, pois tem propriedades especiais para ela.
        char tipo; // r rock f fish p plant

	public:

        Posicionavel(char tipo); //construtor para setar tipo

        char getTipo(); //retorna tipo

		posicao getPosicao();
		void setPosicao();


};

class Peixe: public Posicionavel
{

	private:

		posicao direcao;
		int massa;
        int taxa; //taxa de diminuição
		//funcoes privadas da classe peixe, somente os metodos daqui as utilizam.
        bool explodir(); // tenta se dividir. chama a função diminuir e aloca varios peixes menores no Cubo
		void diminuir(int i);// diminui massa em i pontos por fome/mordida. se a massa chegar a 0, chama a função morrer
		void morrer(); //destroi o objeto e limpa sua posicao no Cubo

	public:
		Peixe(int taxa); //construtor. seta os valores iniciais de massa e direção (aleatoria). chama metodo posicionar.
        //chama o construtor de posicionavel e passa f
        //seta taxa


		void setDirecao(posicao direcao);
		//set direção aleatoria

		posicao getDirecao( );

		int getMassa( );

        int nadar()
		//avança 1 unidade na direção.
		//se encontrar planta morde
		//se encontrar peixe e for maior, come
		//se encontrar peixe e for menor, morre
		//se econtrar peixe e for =, aleatorio come

		Posicionavel** verAFrente();
        //se tem planta/peixe/ retorna referencia
        //vazio retorna nulo
        //se for parede retorna pedra



		bool virar();//muda aleatoriamente sua direção. testar para nao ficar de cabeça para baixo

		void fome(int i); // testa o tempo i. chama a função privada diminuir

		void morder(Posicionavel*);// come planta/peixe e almenta a massa.  checa para ver se nao é uma pedra.
		//chama a funcao privada explodir caso a massa ultrapasse do limite
		//checar se massa do peixe é maior.
		//chama metodo sangrar do mordido.

};

class Planta: public Posicionavel
{

	private:

		int massa;
        int taxa; //taxa de crescimento
		//funcoes privadas da classe planta, somente os metodos daqui as utilizam.
		bool explodir(); // tenta se dividir. chama a função diminuir e aloca varios peixes no Cubo
		void diminuir(int i);// diminui massa em i pontos por fome/mordida. se a massa chegar a 0, chama a função morrer
		void morrer(); //destroi o objeto e limpa sua posicao no Cubo


		void posicionar();
		//pedra e planta sempre sao alocadas no chão
		//planta nao acumula em cima de outras


	public:
		Planta();//construtor. chama metodo posicionar. seta valores iniciais de massa.
        //chama o construtor de posicionavel e passa p
        //seta taxa de crescimento
		int getMassa();

		void crescer(); //aumenta massa e chama a função privada diminuir e explodir caso passe do limite

		void sangrar(); //ocorre ao ser mordido. chama a função privada diminuir


};

class Pedra: public Posicionavel
{

	private:

		void posicionar();
        //pedra e planta sempre sao alocadas no chão
        //pedra acumula em cima das outras
        //chama o construtor de posicionavel e passa r

	public:
		Pedra();//construtor. chama metodo posicionar.


};




#endif // POSICIONAVEL_H






