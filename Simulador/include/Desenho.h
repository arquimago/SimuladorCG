#ifndef DESENHO_H
#define DESENHO_H


class Desenho
{
    public:
        Desenho();
        void desenhar();



        //desenha
        //faz tudo
        virtual ~Desenho();

    protected:

    private:
        void makeStripeImage(int w);
        void init();
        void display();
        void spinDisplay(void);
        void reshape(int w, int h);
        void mouse(int button, int state, int x, int y);
};

#endif // DESENHO_H
