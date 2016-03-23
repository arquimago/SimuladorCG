#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "Desenho.h"
#include "carregadorObj.cpp"
#include "CCamera.cpp"

static Modelo *gold, *orca,*tubarao,*pedra,*planta;
CCamera camera;

int main(int argc, char** argv){
	Desenho opengl(argc,argv);
	opengl.desenhar();
}

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

	delete orca;
	delete gold;
	delete tubarao;
}

void Desenho::init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	
	char *texturasPeixe[] = {NULL, NULL, (char*)"Texturas/GOLDFISH.bmp",(char*)"Texturas/Olho.bmp", NULL};
	tubarao = Modelo::carregarObj((char*)"OBJs/GreatWhite.obj",(char*)"Texturas/GreatWhite.bmp");
	orca = Modelo::carregarObj((char*)"OBJs/KillerWhale.obj",(char*)"Texturas/KillerWhale.bmp");
	pedra = Modelo::carregarObj((char*)"OBJs/rock.obj",(char*)"Texturas/rock.bmp");
	planta = Modelo::carregarObj((char*)"OBJs/alga.obj",(char*)"Texturas/alga.bmp");
	gold = Modelo::carregarObj((char*)"OBJs/GOLDFISH.OBJ", texturasPeixe);
	glDisable(GL_TEXTURE_2D);
   
    camera.Mover( setVetor(0.0, 0.1, 0.0 ));
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
	//desenhar_pedra(0,0,0);
	//desenhar_peixe(0,0,0);
	
	desenhar_planta(0,0,0);
	//desenhar_agua(0,0,0);
	desenhar_agua(0,1,0);
	desenhar_agua(0,0,1);

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
        pedra->desenhar();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Desenho::desenhar_planta(int x, int y, int z)
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(0.51, 0.51, 0.51);
        glColor4f (1.0, 1.0, 1.0, 1.0);
        planta->desenhar();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Desenho::desenhar_peixe(int x, int y, int z)
{
	glEnable(GL_TEXTURE_2D);
	glScalef(0.5, 0.5, 0.5);
  
	glPushMatrix();
        glTranslatef(-1.5, 0.0, 0.0);
        glScalef(0.01, 0.01, 0.01);
        glColor4f (1.0, 1.0, 1.0, 1.0);
        tubarao->desenhar();
	glPopMatrix();
	
    glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
        glScalef(10.0, 10.0, 10.0);
		glColor4f (1.0, 1.0, 1.0, 1.0);
        gold->desenhar();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(1.5, 0.0, 0.0);
        glScalef(10.0, 10.0, 10.0);
		glColor4f (1.0, 1.0, 1.0, 1.0);
        gold->desenhar();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Desenho::desenhar_planta_e_peixe(int x, int y, int z)
{
	glEnable(GL_TEXTURE_2D);

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
	case 'k':      //passinho pra cima
		camera.Mover(setVetor(0.0,-0.3,0.0));
		display();
		break;
	case 'i':      //passinho pra baixo
		camera.Mover(setVetor(0.0,0.3,0.0));
		display();
		break;
	}
}
