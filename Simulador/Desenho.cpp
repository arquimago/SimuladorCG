#include "Desenho.h"
#include "carregadorObj.cpp"
#include "CCamera.cpp"

static Modelo *modeloGold,*modeloPedra,*modeloPlanta;
static CCamera camera;
bool pausado = false;
bool ehCamera = false;
int velocidade=150;

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
	GLfloat luz0_pontual[] = {0.3, 0.5, 0.5, 1.0};
    GLfloat luz0_difuso[] = {0.6, 0.6, 0.6, 1.0};
    GLfloat luz0_especular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat luz0_ambiente[] = {0.1, 0.1, 0.1, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, luz0_pontual);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz0_difuso);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz0_especular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luz0_ambiente);
    
    glEnable(GL_LIGHT0);
	
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	
	char *texturasPeixe[] = {NULL, NULL, (char*)"Texturas/GOLDFISH.bmp",(char*)"Texturas/Olho.bmp", NULL};
	modeloPedra = Modelo::carregarObj((char*)"OBJs/rock.obj",(char*)"Texturas/rock.bmp");
	modeloPlanta = Modelo::carregarObj((char*)"OBJs/alga2.obj",(char*)"Texturas/alga.bmp");
	modeloGold = Modelo::carregarObj((char*)"OBJs/GOLDFISH.OBJ", texturasPeixe);
	glDisable(GL_TEXTURE_2D);
   
	
	camera.RotacaoY(-90.0);
   
    //Para iniciar a câmera de lado é este bloco
	camera.Mover( setVetor(-1 * (y * z) / 2, y / 2 + 0.5, z / 2 + 0.5 ));
	//camera.Mover( setVetor(-3, 1, 1));
			
	//Para iniciar a câmera de cima é este bloco
	//camera.Mover( setVetor(x/2+0.5, (x*z)/2, z/2+0.5 ));
	//camera.RotacaoX(-90.0);
	
}

void Desenho::display(void)
{
	posicao* limites = Ecossistema::getLimites();
	int comprimento = limites->x;
	int altura = limites->y;
	int largura = limites->z;
	
	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	camera.Renderizar();
	
	GLfloat posicao_luz[] = {comprimento / 2 + 1, 2 * altura + 1, largura / 2 + 1};
	//GLfloat posicao_luz[] = {0, 0, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
   
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
    
    glPushMatrix();
    glTranslatef(posicao_luz[0],posicao_luz[1],posicao_luz[2]); 
   
    glEnable(GL_LIGHTING);
    glColor3f (1.0, 1.0, 0.0);
    glutSolidSphere(0.05,50,50);
    glDisable(GL_LIGHTING);
   
    glPopMatrix();
 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	desenhar_eixos();
	
	logica_simulador(altura,largura,comprimento);
	
	if(ehCamera){
		Sleep(150);
		ehCamera=false;
	}else{
		Sleep(velocidade);
	}
	
	for (int k = 1; k<=altura; k++){
		for (int j = 1; j<=largura; j++){
			for (int i = 1; i<=comprimento; i++){
				desenhar_posicao(i,k,j);
			}
		}
	}
	desenhar_agua(comprimento, altura, largura);
	
	glutSwapBuffers();
	glutPostRedisplay();
}

void Desenho::logica_simulador(int altura,int largura,int comprimento)
{
	for (int k = 1; k<=altura; k++)
        {
			for (int j = 1; j<=largura; j++)
            {
                for (int i = 1; i<=comprimento; i++)
                {
					Posicionavel** ocupante = Ecossistema::identificarOcupantes(i,k,j);
                    for (int pos = 1; pos < 3; pos++)
                    {
						if (ocupante[pos] != NULL){
							bool agiu = ((SerVivo*)ocupante[pos])->getAgiu();
							if(!agiu){
								if (pos == 1){
									((Planta*) ocupante[pos])->agir();
								} else {
									((Peixe*) ocupante[pos])->agir();
								}
							}
						}      	
                    }
                }
            }
        }
	
	for (int k = 1; k<=altura; k++)
    {
		for (int j = 1; j<=largura; j++)
        {
            for (int i = 1; i<=comprimento; i++)
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
	
	if (ocupantes[0] != NULL)
	{
		desenhar_pedra(x, y, z);
		return;
	}
	
	if (ocupantes[1] != NULL)
	{
		/*diminuo Y de 0.5 para a planta nascer na base do cubo,
		podendo surgir na superfície da pedra*/
		desenhar_planta(((Planta*) ocupantes[1]), x , y - 0.5 , z);
	}
	
	if (ocupantes[2] != NULL)
	{
		//soma-se 0.25 ao valor de Y para afastar o peixe do centro do cubo
		desenhar_peixe(((Peixe*) ocupantes[2]), x, y + 0.25, z);
	}
}

void Desenho::desenhar_agua(int x, int y, int z)
{
		glColor4f(0.0, 0.0, 1.0, 0.2);
		
		//baixo
    glBegin(GL_POLYGON);
		glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, z + 0.5);
        glVertex3f(x+0.5, 0.5, z + 0.5);
        glVertex3f(x+0.5, 0.5, 0.5);
	glEnd();
	
		//cima
	glBegin(GL_POLYGON);
		glVertex3f(0.5, y + 0.5, 0.5);
        glVertex3f(x + 0.5, y + 0.5, 0.5);
        glVertex3f(x + 0.5, y + 0.5, z + 0.5);
        glVertex3f(0.5, y + 0.5, z + 0.5);
	glEnd();
	
		//esquerda
	glBegin(GL_POLYGON);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, z + 0.5);
		glVertex3f(0.5, y + 0.5, z + 0.5);
        glVertex3f(0.5, y + 0.5, 0.5);
    glEnd();    
	
		//frente
	glBegin(GL_POLYGON);
		glVertex3f(0.5, 0.5, z + 0.5);
        glVertex3f(x + 0.5, 0.5, z + 0.5);
        glVertex3f(x + 0.5, y + 0.5, z + 0.5);
        glVertex3f(0.5, y + 0.5, z + 0.5);
	glEnd();
		
		//direita
	glBegin(GL_POLYGON);
		glVertex3f(x + 0.5, 0.5, 0.5);
        glVertex3f(x + 0.5, 0.5, z + 0.5);
        glVertex3f(x + 0.5, y + 0.5, z + 0.5);
        glVertex3f(x + 0.5, y + 0.5, 0.5);
	glEnd();
		
		//trás
	glBegin(GL_POLYGON);
		glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(x + 0.5, 0.5, 0.5);
        glVertex3f(x + 0.5, y + 0.5, 0.5);
		glVertex3f(0.5, y + 0.5, 0.5);
        
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
        glScalef(0.1 * escala, 0.1 * escala, 0.1 * escala);
        glColor4f (1.0, 1.0, 1.0, 1.0);
        modeloPlanta->desenhar();
	glPopMatrix();
	 
	glDisable(GL_TEXTURE_2D);
}

void Desenho::desenhar_peixe(Peixe* peixe, float x, float y, float z)
{
    posicao* frente = peixe->getDirecao();
    
    float escala = (peixe->getMassa()) / 1000.0; //escala entre 0 e 1
	
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
	
	int anguloX = tabelaAngulos[frente->x + 1][frente->y + 1][frente->z + 1][0];
	int anguloY = tabelaAngulos[frente->x + 1][frente->y + 1][frente->z + 1][1];
	int anguloZ = tabelaAngulos[frente->x + 1][frente->y + 1][frente->z + 1][2];
    
	
	glEnable(GL_TEXTURE_2D);

    glPushMatrix();
		glTranslatef(x, y, z); //posicao
		glScalef(12.0 * escala, 12.0 * escala, 12.0 * escala); //escala peixe
		glColor4f (1.0,1.0 - escala, 1.0 - escala, 1.0); //altera a cor de acordo com a escala
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
	ehCamera=true;
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
	case '1':
		printf("Velocidade 1\n");
		velocidade = 1000;
		break;
	case '2':
		printf("Velocidade 2\n");
		velocidade = 650;
		break;
	case '3':
		printf("Velocidade 3\n");
		velocidade = 150;
		break;
	case '4':
		printf("Velocidade 4\n");
		velocidade = 40;
		break;
	case '5':
		printf("Velocidade 5\n");
		velocidade = 1;
		break;
	case '0':
		pausado = !pausado;
		break;
	case 27:
		exit(42);
		break;
	}
	glutPostRedisplay();
}
