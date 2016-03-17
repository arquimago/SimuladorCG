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
		static void makeStripeImage(int w);
		static void init(void);
		static void display(void);
		static void spinDisplay(void);
		static void reshape(int w, int h);
		static void mouse(int button, int state, int x, int y);
        
};

#endif // DESENHO_H
