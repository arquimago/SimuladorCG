#ifndef DESENHO_H
#define DESENHO_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "Ecossistema.h"
#include <unistd.h>
#include <string.h>


class Desenho
{
	private:
		static void init(int x, int y, int z);
		static void display(void);
		static void reshape(int w, int h);
		static void keyPressed(unsigned char key, int x, int y);
		
		static void desenhar_eixos();
		static void desenhar_posicao(int x, int y, int z);
		static void desenhar_agua(int x, int y, int z);
		static void desenhar_pedra(int x, int y, int z);
		static void desenhar_planta(Planta* planta, float x, float y, float z);
		static void desenhar_peixe(Peixe* peixe, float x, float y, float z);
	
	
    protected:
		
	public:
        Desenho(int argc, char** argv,int x, int y, int z);
        void desenhar();
};

#endif // DESENHO_H
