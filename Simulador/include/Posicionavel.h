/*#ifndef POSICIONAVEL_H
#define POSICIONAVEL_H


class Posicionavel
{
    public:
        Posicionavel();
        virtual ~Posicionavel();

    protected:

    private:
};

#endif // POSICIONAVEL_H*/

#ifndef POSICIONAVEL_H
#define POSICIONAVEL_H

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
// usado para posicao e direcao.
//direcao � +1, 0 ou -1 em cada um dos eixos, n�o podendo ser 0 nos tr�s
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
        //pedra e planta sobrecarregam essa fun��o, pois tem propriedades especiais para ela.
        char tipo; // r rock f fish p plant

	public:

        Posicionavel(char tipo); //construtor para setar tipo

        char getTipo(); //retorna tipo

		posicao getPosicao();
		void setPosicao(posicao posicaoNova, int i);

		void agir(); //planta e peixe vão sobrescrever esse metodo


};

class Peixe: public Posicionavel
{

	private:

		posicao direcao;
		int massa;
        int taxa; //taxa de diminui��o
		//funcoes privadas da classe peixe, somente os metodos daqui as utilizam.
        bool explodir(); // tenta se dividir. chama a fun��o diminuir e aloca varios peixes menores no Cubo
		void diminuir(int i);// diminui massa em i pontos por fome/mordida. se a massa chegar a 0, chama a fun��o morrer
		void morrer(); //destroi o objeto e limpa sua posicao no Cubo

        void nadar();
		//avan�a 1 unidade na dire��o.


        Posicionavel** verAFrente();
        //se tem planta/peixe/ retorna referencia
        //vazio retorna nulo
        //se for parede retorna pedra

        void virar();//muda aleatoriamente sua dire��o. testar para nao ficar de cabe�a para baixo

	public:
		Peixe(int taxa); //construtor. seta os valores iniciais de massa e dire��o (aleatoria). chama metodo posicionar.
        //chama o construtor de posicionavel e passa f
        //seta taxa


        void agir();
        //usa ve a frente, muda direção de peixe
        //se encontrar planta morde
		//se encontrar peixe e for maior, come
		//se encontrar peixe e for menor, morre

        posicao getDirecao();
		int getMassa( );

		void fome(int i); // testa o tempo i. chama a fun��o privada diminuir

		void morder(Posicionavel*);// come planta/peixe e almenta a massa.  checa para ver se nao � uma pedra.
		//chama a funcao privada explodir caso a massa ultrapasse do limite
		//checar se massa do peixe � maior.
		//chama metodo sangrar do mordido.
		//chama metodo crescer do peixe de acordo com o retorno de sangrar do mordido

		int sangrar();
		//essa fun��o chama a fun��o morrer.
		//retorna toda a massa do peixe

};

class Planta: public Posicionavel
{

	private:

		int massa;
        int taxa; //taxa de crescimento
		//funcoes privadas da classe planta, somente os metodos daqui as utilizam.
		bool explodir(); // tenta se dividir. chama a fun��o diminuir e aloca varios peixes no Cubo
		int diminuir(int i);// diminui massa em i pontos por mordida. se a massa chegar a 0, chama a fun��o morrer. retorna massa perdida
		void morrer(); //destroi o objeto e limpa sua posicao no Cubo

		void crescer(); //aumenta massa e chama a fun��o privada diminuir e explodir caso passe do limite
		void posicionar();
		//pedra e planta sempre sao alocadas no ch�o
		//planta nao acumula em cima de outras


	public:
		Planta();//construtor. chama metodo posicionar. seta valores iniciais de massa.
        //chama o construtor de posicionavel e passa p
        //seta taxa de crescimento
		int getMassa();
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
        //chama o construtor de posicionavel e passa r

	public:
		Pedra();//construtor. chama metodo posicionar.


};




#endif // POSICIONAVEL_H


