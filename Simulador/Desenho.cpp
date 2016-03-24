#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "Desenho.h"
#include "Ecossistema.cpp"
#include "carregadorObj.cpp"
#include "CCamera.cpp"

static Modelo *modeloGold, *modeloOrca,*modeloTubarao,*modeloPedra,*modeloPlanta;
static CCamera camera;

Desenho::Desenho(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (700, 700);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Aquario");
	
	init();
	
	glutDisplayFunc(Desenho::display); 
	glutKeyboardFunc(Desenho::keyPressed);
	glutReshapeFunc(Desenho::reshape);
}

void Desenho::desenhar()
{   
	glutMainLoop();

	delete modeloOrca;
	delete modeloGold;
	delete modeloTubarao;
}

void Desenho::init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	
	char *texturasPeixe[] = {NULL, NULL, (char*)"Texturas/GOLDFISH.bmp",(char*)"Texturas/Olho.bmp", NULL};
	//modeloTubarao = Modelo::carregarObj((char*)"OBJs/GreatWhite.obj",(char*)"Texturas/GreatWhite.bmp");
	//modeloOrca = Modelo::carregarObj((char*)"OBJs/KillerWhale.obj",(char*)"Texturas/KillerWhale.bmp");
	modeloPedra = Modelo::carregarObj((char*)"OBJs/rock.obj",(char*)"Texturas/rock.bmp");
	modeloPlanta = Modelo::carregarObj((char*)"OBJs/alga.obj",(char*)"Texturas/alga.bmp");
	modeloGold = Modelo::carregarObj((char*)"OBJs/GOLDFISH.OBJ", texturasPeixe);
	glDisable(GL_TEXTURE_2D);
   
    camera.Mover( setVetor(0.0, 0.0, 0.5 ));
    camera.ParaFrente( 1.0 );
}

void Desenho::display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	camera.Renderizar();
 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	desenhar_eixos();
	
	posicao* limites = Ecossistema::getLimites();
	int comprimento = limites->x;
	int altura = limites->y;
	int largura = limites->z;
	for (int k=1; k<=altura; k++)
            for (int j=1; j<=largura; j++)
                for (int i=1; i<=comprimento; i++)
			desenhar_posicao(i,k,j);
      
	glutSwapBuffers();
}

void Desenho::desenhar_eixos()
{
	glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f (1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        
        glColor3f (0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
      
        glColor3f (1.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 1.0);    
    glEnd();
}

void Desenho::desenhar_posicao (int x, int y, int z)
{
	desenhar_agua(x, y, z);
	
	Posicionavel** ocupantes = Ecossistema::identificarOcupantes(x,y,z);
	Pedra* pedra = (Pedra*) ocupantes[0];
	Planta* planta = (Planta*) ocupantes[1];
	Peixe* peixe = (Peixe*) ocupantes[2];
	
	if (pedra != NULL)
	{
		desenhar_pedra(x, y, z);
		return;
	}
	
	if (planta != NULL)
	{
		desenhar_planta(planta, x, y-0.25, z);
	}
	
	if (peixe != NULL)
	{
		desenhar_peixe(peixe, x, y+0.25, z);
	}
}

void Desenho::desenhar_agua(int x, int y, int z)
{
	//FRENTE
    glBegin(GL_QUADS);
        glColor4f(0.0, 0.0, 1.0, 0.5);
        glVertex3f( 0.5+x, -0.5+y, -0.5+z);
        glVertex3f( 0.5+x,  0.5+y, -0.5+z);  
        glVertex3f(-0.5+x,  0.5+y, -0.5+z);
        glVertex3f(-0.5+x, -0.5+y, -0.5+z);    
    glEnd();
    
    //TRASEIRA
	glBegin(GL_QUADS);
		//glColor4f (0.0, 0.0, 1.0, 1.0);
		glVertex3f( 0.5+x, -0.5+y, 0.5+z);
		glVertex3f( 0.5+x,  0.5+y, 0.5+z);
		glVertex3f(-0.5+x,  0.5+y, 0.5+z);
		glVertex3f(-0.5+x, -0.5+y, 0.5+z);
    glEnd();
    
	//DIREITA
	glBegin(GL_POLYGON);
		//glColor4f (0.0, 0.0, 1.0, 1.0);
		glVertex3f(0.5+x, -0.5+y, -0.5+z);
		glVertex3f(0.5+x,  0.5+y, -0.5+z);
		glVertex3f(0.5+x,  0.5+y,  0.5+z);
		glVertex3f(0.5+x, -0.5+y,  0.5+z);
	glEnd();
    
    //ESQUERDA
    glBegin(GL_POLYGON);
		//glColor4f (0.0, 0.0, 1.0, 1.0);
		glVertex3f(-0.5+x, -0.5+y,  0.5+z);
		glVertex3f(-0.5+x,  0.5+y,  0.5+z);
		glVertex3f(-0.5+x,  0.5+y, -0.5+z);
		glVertex3f(-0.5+x, -0.5+y, -0.5+z);
	glEnd();
 
	//TOPO
	glBegin(GL_POLYGON);
		//glColor4f (0.0, 0.0, 1.0, 1.0);
		glVertex3f( 0.5+x,  0.5+y,  0.5+z);
		glVertex3f( 0.5+x,  0.5+y, -0.5+z);
		glVertex3f(-0.5+x,  0.5+y, -0.5+z);
		glVertex3f(-0.5+x,  0.5+y,  0.5+z);
	glEnd();
 
	//BASE
	glBegin(GL_POLYGON);
		//glColor4f (0.0, 0.0, 1.0, 1.0);
		glVertex3f( 0.5+x, -0.5+y, -0.5+z);
		glVertex3f( 0.5+x, -0.5+y,  0.5+z);
		glVertex3f(-0.5+x, -0.5+y,  0.5+z);
		glVertex3f(-0.5+x, -0.5+y, -0.5+z);
	glEnd();
}

void Desenho::desenhar_pedra(int x, int y, int z)
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(1, 1, 1);
        glColor4f (1.0, 1.0, 1.0, 1.0);
        modeloPedra->desenhar();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Desenho::desenhar_planta(Planta* planta, int x, int y, int z)
{
	glEnable(GL_TEXTURE_2D);

    float escala = (planta->getMassa())/1000;
	
	glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(0.51*escala, 0.51*escala, 0.51*escala);
        glColor4f (1.0, 1.0, 1.0, 1.0);
        modeloPlanta->desenhar();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}


void Desenho::desenhar_peixe(Peixe* peixe, int x, int y, int z)
{
    posicao *direcao = peixe->getDirecao();

    float escala = (peixe->getMassa())/1000;
    float angulo;

    if (direcao->x > 0 && direcao->y > 0 && direcao->z > 0)
    {

    }
    if (direcao->x > 0 && direcao->y < 0 && direcao->z > 0)
    {

    }
    if (direcao->x < 0 && direcao->y > 0 && direcao->z > 0)
    {

    }
    if (direcao->x < 0 && direcao->y < 0 && direcao->z > 0)
    {

    }
    if (direcao->x > 0 && direcao->y > 0 && direcao->z < 0)
    {

    }
    if (direcao->x > 0 && direcao->y < 0 && direcao->z < 0)
    {

    }
    if (direcao->x < 0 && direcao->y > 0 && direcao->z < 0)
    {

    }
    if (direcao->x < 0 && direcao->y < 0 && direcao->z < 0)
    {

    }
    
    //Lados
    if (direcao->x == 0 && direcao->z == 0 && direcao->y>0)
    {

    }
    if (direcao->x == 0 && direcao->z == 0 && direcao->y<0)
    {

    }
    if (direcao->x > 0 && direcao->z == 0 && direcao->y == 0)
    {

    }
    if (direcao->x < 0 && direcao->z == 0 && direcao->y == 0)
    {

    }
    if (direcao->x == 0 && direcao->z < 0 && direcao->y == 0)
    {

    }
    if (direcao->x == 0 && direcao->z > 0 && direcao->y == 0)
    {

    }
	
	glEnable(GL_TEXTURE_2D);

    glPushMatrix();
		glTranslatef(x, y, z);
        glScalef(10.0*escala, 10.0*escala, 10.0*escala);
		glColor4f (1.0, 1.0, 1.0, 1.0);
		glRotatef(angulo, direcao->x, direcao->y, direcao->z);
        modeloGold->desenhar();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Desenho::reshape(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -100.0, 100.0);
   
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Desenho::keyPressed (unsigned char key, int x, int y)
{
	key = tolower(key);
	switch (key) 
	{
	case 'a':	//roda pra esquerda
		camera.RotacaoY(5.0);
		display();
		break;
	case 'd':	//roda pra direita
		camera.RotacaoY(-5.0);
		display();
		break;
	case 'w':	//anda pra frente	
		camera.ParaFrente(-0.1) ;
		display();
		break;
	case 's':	//anda pra trás
		camera.ParaFrente(0.1) ;
		display();
		break;
	case 'q':      //roda pra cima
		camera.RotacaoX(5.0);
		display();
		break;
	case 'e':	//roda pra baixo	
		camera.RotacaoX(-5.0);
		display();
		break;
	case 'j':	//passinho pra esquerda
		camera.ParaOLado(-0.1);
		display();
		break;
	case 'l':	//passinho pra direita
		camera.ParaOLado(0.1);
		display();
		break;
	case 'i':      //passinho pra cima
		camera.Mover(setVetor(0.0,0.3,0.0));
		display();
		break;
	case 'k':      //passinho pra baixo
		camera.Mover(setVetor(0.0,-0.3,0.0));
		display();
		break;
	}
}
