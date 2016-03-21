#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "Desenho.h"
#include "carregadorObj.cpp"

static float posCameraX,posCameraY,posCameraZ;
static float posVisaoX,posVisaoY,posVisaoZ;
static Modelo *gold, *orca,*tubarao,*pedra,*planta;

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
   
	posCameraX = 0.1;
	posCameraY = 0.0;
	posCameraZ = 0.0;
}

void Desenho::display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(posCameraX, posCameraY, posCameraZ, posVisaoX, posVisaoY, posVisaoZ, 0.0, 1.0, 0.0);
 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//desenhar_peixe(0,0,0);
	//desenhar_pedra(0,0,0);
	desenhar_planta(0,0,0);
	desenhar_agua(0,0,0);
	desenhar_agua(0,1,0);
	desenhar_agua(0,0,1);
	desenhar_eixos();

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
        glScalef(0.01, 0.01, 0.01);
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
	float angulo = 2*M_PI/180;
	switch(key){
		case 'a' : //Esquerda
            posCameraZ = posCameraZ+0.01;
            posVisaoZ = posVisaoZ+0.01;
            break;
		case 'd' : //Direita
            posCameraZ = posCameraZ-0.01;
            posVisaoZ = posVisaoZ-0.01;
            break;
        case 'w' : //Cima
            posCameraY = posCameraY+0.01;
            posVisaoY = posVisaoY+0.01;
            break;
		case 's' : //Baixo
            posCameraY = posCameraY-0.01;
            posVisaoY = posVisaoY-0.01;
            break;
        case 'q' : //+Zoom
            break;
        case 'e' : //-Zoom
            break;
        case 'j' : //GiraEsquerda
            posCameraX =  posCameraX*cos(-angulo) + posCameraZ*sin(-angulo);
            posCameraZ = -posCameraX*sin(-angulo) + posCameraZ*cos(-angulo);
            break;
        case 'l' : //GiraDireita
            posCameraX =  posCameraX*cos(angulo) + posCameraZ*sin(angulo);
            posCameraZ = -posCameraX*sin(angulo) + posCameraZ*cos(angulo);
            break;
		case 'i' : //GiraCima       
            break;
		case 'k' : //GiraBaixo         
            break;
    }
    glutPostRedisplay();
}
