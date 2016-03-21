#ifndef DESENHO_H
#define DESENHO_H

class Desenho
{
    public:
        Desenho(int argc, char** argv);
        void desenhar();
        //~Desenho();

    protected:

    
	private:
		static void init(void);
		static void display(void);
		static void reshape(int w, int h);
		static void keyPressed(unsigned char key, int x, int y);
		
		static void desenhar_eixos();
		static void desenhar_agua(int x, int y, int z);
		static void desenhar_pedra(int x, int y, int z);
		static void desenhar_planta(int x, int y, int z);
		static void desenhar_peixe(int x, int y, int z);
		static void desenhar_planta_e_peixe(int x, int y, int z);
};

#endif // DESENHO_H
