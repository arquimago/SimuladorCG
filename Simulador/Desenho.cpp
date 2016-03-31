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
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static Modelo *modeloGold, *modeloPedra,*modeloPlanta;
static CCamera camera;


int main (int argc, char** argv)
{
	srand((unsigned)time(NULL));
	srand(rand());
		
	int qtdPeixe=2;
    int qtdPedra=20;
    int qtdPlanta=2;
    int altura=3;  //y     0  2
    int largura=6; //z  0  5
    int comprimento=4;//x 0 3
    int taxaCrescimentoPlanta=15;
    int taxaDiminuicaoPeixe=10;
	
	char lixo[7];
	
	//Para leitura do arquivo basta descomentar o bloco abaixo
	
	FILE *arqInput;
	arqInput=fopen(argv[1],"r");
	if(arqInput==NULL){
		printf("Falha no acesso ao arquivo");
		exit(42);
	}
		
    //inicializar cubo
    //inicializar posicoes de pedras, plantas e peixes
    Ecossistema::inicializar(comprimento,altura,largura);
	Desenho opengl(argc,argv,comprimento,altura,largura);
	
	fscanf(arqInput," %d %d %d\n",&largura,&altura,&comprimento);
	fscanf(arqInput," %s %d %d\n",&lixo,&qtdPeixe,&taxaDiminuicaoPeixe);
	int taxaPeixe = taxaDiminuicaoPeixe;
	//Por algum motivo satanico a taxaDiminuicaoPeixe se perde na proxima linha
	//então salvei em taxaPeixe
	fscanf(arqInput," %s %d %d\n",&lixo,&qtdPlanta, &taxaCrescimentoPlanta);
	fscanf(arqInput," %s %d",&lixo,&qtdPedra);
	   
    
    for (int i=0 ; i < qtdPedra; i++) new Pedra();
    for (int i=0 ; i < qtdPlanta; i++) new Planta(taxaCrescimentoPlanta);
    //Sobre taxaPeixe leia linha 53
	for (int i=0 ; i < qtdPeixe; i++) new Peixe(taxaPeixe);
	
	glutMainLoop();
}

Desenho::Desenho(int argc, char** argv,int x, int y, int z)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (700, 700);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Aquario");
	
	init(x,y,z);
	
	glutDisplayFunc(Desenho::display); 
	glutKeyboardFunc(Desenho::keyPressed);
	glutReshapeFunc(Desenho::reshape);
}

void Desenho::init(int x, int y, int z)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	
	char *texturasPeixe[] = {NULL, NULL, (char*)"Texturas/GOLDFISH.bmp",(char*)"Texturas/Olho.bmp", NULL};
	modeloPedra = Modelo::carregarObj((char*)"OBJs/rock.obj",(char*)"Texturas/rock.bmp");
	modeloPlanta = Modelo::carregarObj((char*)"OBJs/alga.obj",(char*)"Texturas/alga.bmp");
	modeloGold = Modelo::carregarObj((char*)"OBJs/GOLDFISH.OBJ", texturasPeixe);
	glDisable(GL_TEXTURE_2D);
   
	
	camera.RotacaoY(-90.0);
   
    //Para iniciar a câmera de lado é este bloco
	camera.Mover( setVetor(-1*(y*z)/2, y/2+0.5, z/2+0.5 ));
			
	//Para iniciar a câmera de cima é este bloco
	//camera.Mover( setVetor(x/2+0.5, (x*z)/2, z/2+0.5 ));
	//camera.RotacaoX(-90.0);
	
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
        {
			for (int j=1; j<=largura; j++)
            {
                for (int i=1; i<=comprimento; i++)
                {
					Posicionavel** ocupante = Ecossistema::identificarOcupantes(i,k,j);
                    for (int pos = 1; pos < 3; pos++)
                    {
						if (ocupante[pos] != NULL){
							bool agiu = ((SerVivo*)ocupante[pos])->getAgiu();
							Posicionavel** morto = Ecossistema::identificarOcupantes(0,0,0);
							if(!agiu){
								if (pos == 1){
									((Planta*) ocupante[pos])->agir();
								} else {
									((Peixe*) ocupante[pos])->agir();
								}
							}
							delete morto[2];
							delete morto[1];
										
						}                      						 
                    }
                }
            }
        }
	
	for (int k=1; k<=altura; k++)
    {
		for (int j=1; j<=largura; j++)
        {
            for (int i=1; i<=comprimento; i++)
            {
				Posicionavel** ocupante = Ecossistema::identificarOcupantes(i,k,j);
                for (int pos = 1; pos < 3; pos++)
                {
					if (ocupante[pos] != NULL){
						bool agiu = ((SerVivo*)ocupante[pos])->getAgiu();
						if(agiu){
							((SerVivo*)ocupante[pos])->setAgiu();
						}
					}
				}
            }
        }
    }
	
	for (int k=1; k<=altura; k++){
		for (int j=1; j<=largura; j++){
			for (int i=1; i<=comprimento; i++){
				desenhar_posicao(i,k,j);
			}
		}
	}
	desenhar_agua(comprimento, altura, largura);
	
    Sleep(150);
	
	glutSwapBuffers();
	glutPostRedisplay();
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
	
	if (pedra != NULL)
	{
		desenhar_pedra(x, y, z);
		return;
	}
	
	if (planta != NULL)
	{
		desenhar_planta(planta, x , y-0.25 , z);
		
	}
	
	if (peixe != NULL)
	{
		desenhar_peixe(peixe, x, y+0.25, z);
	}
}

void Desenho::desenhar_agua(int x, int y, int z)
{
		glColor4f(0.0, 0.0, 1.0, 0.2);
		
		//baixo
    glBegin(GL_POLYGON);
		glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, z+0.5);
        glVertex3f(x+0.5, 0.5, z+0.5);
        glVertex3f(x+0.5, 0.5, 0.5);
	glEnd();
	
		//cima
	glBegin(GL_POLYGON);
		glVertex3f(0.5, y+0.5, 0.5);
        glVertex3f(x+0.5, y+0.5, 0.5);
        glVertex3f(x+0.5, y+0.5, z+0.5);
        glVertex3f(0.5, y+0.5, z+0.5);
	glEnd();
	
		//esquerda
	glBegin(GL_POLYGON);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, z+0.5);
		glVertex3f(0.5, y+0.5, z+0.5);
        glVertex3f(0.5, y+0.5, 0.5);
    glEnd();    
	
		//frente
	glBegin(GL_POLYGON);
		glVertex3f(0.5, 0.5, z+0.5);
        glVertex3f(x+0.5, 0.5, z+0.5);
        glVertex3f(x+0.5, y+0.5, z+0.5);
        glVertex3f(0.5, y+0.5, z+0.5);
	glEnd();
		
		//direita
	glBegin(GL_POLYGON);
		glVertex3f(x+0.5, 0.5, 0.5);
        glVertex3f(x+0.5, 0.5, z+0.5);
        glVertex3f(x+0.5, y+0.5, z+0.5);
        glVertex3f(x+0.5, y+0.5, 0.5);
	glEnd();
		
		//trás
	glBegin(GL_POLYGON);
		glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(x+0.5, 0.5, 0.5);
        glVertex3f(x+0.5, y+0.5, 0.5);
		glVertex3f(0.5, y+0.5, 0.5);
        
	glEnd();
}

void Desenho::desenhar_pedra(int x, int y, int z)
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(0.9999, 0.9999, 0.9999);
        glColor4f (1.0, 1.0, 1.0, 1.0);
        modeloPedra->desenhar();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Desenho::desenhar_planta(Planta* planta, float x, float y, float z)
{
	glEnable(GL_TEXTURE_2D);

    float escala = (planta->getMassa())/1000.0;
	glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(escala, escala, escala);
        glColor4f (1.0, 1.0, 1.0, 1.0);
        modeloPlanta->desenhar();
	glPopMatrix();
	 
	glDisable(GL_TEXTURE_2D);
}


void Desenho::desenhar_peixe(Peixe* peixe, float x, float y, float z)
{
    posicao* frente = peixe->getDirecao();
    
    float escala = (peixe->getMassa())/1000.0;
	//printf("Posicao x = %.2f y = %.2f z = %.2f \n", x,y,z);
	
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
	
	int anguloX = tabelaAngulos[frente->x+1][frente->y+1][frente->z+1][0];
	int anguloY = tabelaAngulos[frente->x+1][frente->y+1][frente->z+1][1];
	int anguloZ = tabelaAngulos[frente->x+1][frente->y+1][frente->z+1][2];
    
	
	glEnable(GL_TEXTURE_2D);

    glPushMatrix();
		glTranslatef(x, y, z); //posicao
		glScalef(12.0*escala, 12.0*escala, 12.0*escala); //escala peixe
		glColor4f (1.0, 1.0, 1.0, 1.0);
		glRotatef(anguloX,1,0,0);
		glRotatef(anguloY,0,1,0);
		glRotatef(anguloZ,0,0,1);
        modeloGold->desenhar();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void Desenho::reshape(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, -100.0, 100.0);
	gluPerspective(40.0,(GLdouble)w/(GLdouble)h,0.5,20.0);
   
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
		break;
	case 'd':	//roda pra direita
		camera.RotacaoY(-5.0);
		break;
	case 'w':	//anda pra frente	
		camera.ParaFrente(-0.1);
		break;
	case 's':	//anda pra trás
		camera.ParaFrente(0.1) ;
		break;
	case 'q':      //roda pra cima
		camera.RotacaoX(5.0);
		break;
	case 'e':	//roda pra baixo	
		camera.RotacaoX(-5.0);
		break;
	case 'j':	//passinho pra esquerda
		camera.ParaOLado(-0.1);
		break;
	case 'l':	//passinho pra direita
		camera.ParaOLado(0.1);
		break;
	case 'i':      //passinho pra cima
		camera.Mover(setVetor(0.0,0.3,0.0));
		break;
	case 'k':      //passinho pra baixo
		camera.Mover(setVetor(0.0,-0.3,0.0));
		break;
	}
	glutPostRedisplay();
}
