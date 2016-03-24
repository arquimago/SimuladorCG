#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "Desenho.h"
#include "Ecossistema.cpp"
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

void Desenho::desenhar_posicionavel (int x, int y, int z)
{
	Posicionavel** ocupantes = Ecossistema::identificarOcupantes(x,y,z);
	
	Desenho::desenhar_agua(x,y,z);
	
	if (ocupantes[0] != NULL)
	{
		Desenho::desenhar_pedra(x,y,z);
		return; //sai da função
	}
	
	if (ocupantes[1] != NULL)
	{
		Desenho::desenhar_planta(x,y,z);
	}
	
	if (ocupantes[2] != NULL)
	{
		Desenho::desenhar_peixe(x,y,z);
	}
	
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
	//desenhar_pedra(0,0,0);
	desenhar_peixe(0,0,0);
	
	//desenhar_planta(0,0,0);
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
    //escala
    //ROTACIONAR PARA DIRECAO x y z
    //localização x y z
    /*Posicionavel** ocupante = Ecossistema::identificarOcupantes(x,y,z);
    Peixe* peixe = (Peixe*) ocupante[2];

    posicao* frente = peixe->getDirecao();
    posicao direcao;
    direcao.x = frente->x;
    direcao.y = frente->y;
    direcao.z = frente->z;

    float escala = (peixe->getMassa())/1000;
    float angulo,vetorx,vetory,vetorz = 0;*/

	float escala=1;
	posicao direcao;
	direcao.x=1;
	direcao.y=1;
	direcao.z=1;
	


    //rotacionar peixe
    //definir angulo,vetorx,vetory,vetorz
    //diagonais
    if (direcao.x > 0 && direcao.y > 0 && direcao.z > 0)
    {

    }
    if (direcao.x > 0 && direcao.y < 0 && direcao.z > 0)
    {

    }
    if (direcao.x < 0 && direcao.y > 0 && direcao.z > 0)
    {

    }
    if (direcao.x < 0 && direcao.y < 0 && direcao.z > 0)
    {

    }
    if (direcao.x > 0 && direcao.y > 0 && direcao.z < 0)
    {

    }
    if (direcao.x > 0 && direcao.y < 0 && direcao.z < 0)
    {

    }
    if (direcao.x < 0 && direcao.y > 0 && direcao.z < 0)
    {

    }
    if (direcao.x < 0 && direcao.y < 0 && direcao.z < 0)
    {

    }
    //lados
    if (direcao.x == 0 && direcao.z == 0 && direcao.y>0)
    {

    }
    if (direcao.x == 0 && direcao.z == 0 && direcao.y<0)
    {

    }
    if (direcao.x > 0 && direcao.z == 0 && direcao.y == 0)
    {

    }
    if (direcao.x < 0 && direcao.z == 0 && direcao.y == 0)
    {

    }
    if (direcao.x == 0 && direcao.z < 0 && direcao.y == 0)
    {

    }
    if (direcao.x == 0 && direcao.z > 0 && direcao.y == 0)
    {

    }

	
	glEnable(GL_TEXTURE_2D);
	glScalef(0.5, 0.5, 0.5);

    glPushMatrix();
		glTranslatef(x, y, z); //posicao
        glScalef(10.0*escala, 10.0*escala, 10.0*escala); //escala peixe
		glColor4f (1.0, 1.0, 1.0, 1.0);
		///glRotatef(angulo,vetorx,vetory,vetorz);
		glRotatef(180,direcao.x,direcao.y,direcao.z);
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
