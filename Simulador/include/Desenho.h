#ifndef DESENHO_H
#define DESENHO_H

class Desenho
{
    public:
        Desenho(int argc, char** argv);
        int desenhar();



        //desenha
        //faz tudo
        //virtual ~Desenho();

    protected:

    
	private:
		static void init(void);
		static void display(void);
		static void reshape(int w, int h);
		static void mouse(int button, int state, int x, int y);
		static void specialKeys(int key, int x, int y);
		static void desenhar_objeto();
};

#endif // DESENHO_H
