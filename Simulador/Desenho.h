#ifndef DESENHO_H
#define DESENHO_H
#include "Posicionavel.cpp"

class Desenho
{
    public:
        Desenho(int argc, char** argv,int x, int y, int z);
        void desenhar();
        //~Desenho();

    protected:

    
	private:
		static void init(int x, int y, int z);
		static void display(void);
		static void reshape(int w, int h);
		static void keyPressed(unsigned char key, int x, int y);
		
		static void desenhar_eixos();
		static void desenhar_posicao(int x, int y, int z);
		static void desenhar_agua(int x, int y, int z);
		static void desenhar_pedra(int x, int y, int z);
		static void desenhar_planta(Planta* planta, int x, int y, int z);
		static void desenhar_peixe(Peixe* peixe, int x, int y, int z);
};

#endif // DESENHO_H
