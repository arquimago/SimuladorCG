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
#include "stdio.h"

static Modelo *modeloGold, *modeloOrca,*modeloTubarao,*modeloPedra,*modeloPlanta;
static CCamera camera;

int main (int argc, char** argv)
{
	//ler arquivo de beatriz

    int qtdPeixe = 3;
    int qtdPedra = 20;
    int qtdPlanta = 4;
    int altura = 3;  //y     0  2
    int largura = 6; //z  0  5
    int comprimento = 4;//x 0 3
    int taxaCrescimentoPlanta = 15;
    int taxaDiminuicaoPeixe = 10;

    //inicializar cubo
    //inicializar posicoes de pedras, plantas e peixes
    Ecossistema::inicializar(comprimento,altura,largura);
	Desenho opengl(argc,argv);

    //posicionar plantas pedras e peixes
    //
    for (int i=0 ; i <= qtdPedra; i++) new Pedra();
    for (int i=0 ; i <= qtdPlanta; i++) new Planta(taxaCrescimentoPlanta);
    for (int i=0 ; i <= qtdPeixe; i++) new Peixe(taxaDiminuicaoPeixe);

    //programa rodando
    while(true)
    {   
    	opengl.desenhar();
        for (int k=1; k<=altura; k++)
        {
            for (int j=1; j<=largura; j++)
            {
                for (int i=1; i<=comprimento; i++)
                {
                    Posicionavel** ocupante = Ecossistema::identificarOcupantes(i,k,j);
                    for (int pos = 0; pos < 3; pos++)
                    {
                        if (ocupante[pos] != NULL) //TEM ALGO
                            ocupante[pos]->agir();
                    }

                }
            }
        }
    }	
	
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
	
	desenhar_agua(comprimento, altura, largura);
	
	for (int k=1; k<=altura; k++){
		for (int j=1; j<=largura; j++){
			for (int i=1; i<=comprimento; i++){
				desenhar_posicao(i,k,j);
				//desenhar_pedra(i,k,j);
			}
		}
	}
      
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
	Posicionavel** ocupantes = Ecossistema::identificarOcupantes(x,y,z);
	Pedra* pedra = (Pedra*) ocupantes[0];
	Planta* planta = (Planta*) ocupantes[1];
	Peixe* peixe = (Peixe*) ocupantes[2];
	
	//desenhar_planta(planta, 1, 1, 1);
	
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
		//desenhar_peixe(peixe, x, y+0.25, z);
	}
	
	//desenhar_agua(x, y, z);
}

void Desenho::desenhar_agua(int x, int y, int z)
{
	//FRENTE
    glBegin(GL_QUADS);
        glColor4f(0.0, 0.0, 1.0, 0.2);
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

    float escala = (planta->getMassa())/1000.0;
	
	glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(3*escala, 3*escala, 3*escala);
        glColor4f (1.0, 1.0, 1.0, 1.0);
        modeloPlanta->desenhar();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}


void Desenho::desenhar_peixe(Peixe* peixe, int x, int y, int z)
{
    posicao* frente = peixe->getDirecao();
    posicao direcao;
    direcao.x = frente->x;
    direcao.y = frente->y;
    direcao.z = frente->z;

    float escala = (peixe->getMassa())/1000;
	//até aqui não mudei
    
	int tabelaAngulos[3][3][3][3] = {
		{
			{
				{315,225,0},{0,270,45},{45,315,0}
			},{
				{0,225,0},{0,270,0},{0,315,0}
			},{
				{45,225,0},{0,270,315},{315,315,0}
			}
		},{
			{
				{45,180,0},{90,0,0},{45,0,0}
			},{
				{0,180,0},{0,0,0},{0,0,0}
			},{
				{315,180,0},{270,0,0},{315,0,0}
			}
		},{
			{
				{315,135,0},{45,90,0},{45,45,0}
			},{
				{0,135,0},{0,90,0},{0,45,0}
			},{
				{45,135,0},{315,90,0},{315,45,0}
			}
		}
	};
	int anguloX = tabelaAngulos[direcao.x+1][direcao.y+1][direcao.z+1][0];
	int anguloY = tabelaAngulos[direcao.x+1][direcao.y+1][direcao.z+1][1];
	int anguloZ = tabelaAngulos[direcao.x+1][direcao.y+1][direcao.z+1][2];
    
	
	glEnable(GL_TEXTURE_2D);
	glScalef(0.5, 0.5, 0.5);

    glPushMatrix();
		glScalef(10.0*escala, 10.0*escala, 10.0*escala); //escala peixe
		glColor4f (1.0, 1.0, 1.0, 1.0);
		glTranslatef(0,0,0);
		glRotatef(anguloX,1,0,0);
		glRotatef(anguloY,0,1,0);
		glRotatef(anguloZ,0,0,1);
		glTranslatef(x, y, z); //posicao
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
