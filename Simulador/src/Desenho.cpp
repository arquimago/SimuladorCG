#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "Desenho.h"
#include "CarregadorObj.cpp"

static float posCameraX,posCameraY,posCameraZ;
static Modelo* peixe;  //OBJETOS DO CENARIO

Desenho::Desenho(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (700, 700); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
  
	init ();
	
	char *texturasPeixe[] = {NULL, NULL, (char*)"GOLDFISH.bmp",(char*)"Olho.bmp", NULL};  //NOME DAS TEXTURAS DO GOLDFISH (UMA PARA CADA PARTE DO MODELO)
   
	peixe = Modelo::carregarObj((char*)"gold.obj"); //textura é carregada automaticamente
}
	

int Desenho::desenhar()
{
   glutDisplayFunc(Desenho::display); 
   glutReshapeFunc(Desenho::reshape); 
   //glutMouseFunc(Desenho::mouse);
   //glutSpecialFunc(specialKeys);
   
   glutMainLoop();
   
   return 0;
}

void Desenho::init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
  
   // ativa teste de profundidade
   // o que acontece se isso nÃ£o for feito?
   glEnable(GL_DEPTH_TEST);
   glShadeModel (GL_SMOOTH);
   
   posCameraX = 0.3;
   posCameraY = 0.1;
   posCameraZ = 0;
}

void Desenho::display(void)
{
   //limpeza do zbuffer deve ser feita a cada desenho da tela
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
 
   gluLookAt (posCameraX, posCameraY, posCameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 
   //desenhar_luz(); 
   //desenhar_eixos();
   desenhar_objeto();
    
   glutSwapBuffers();
}

//desenha objeto
void Desenho::desenhar_objeto(){	
   //MATERIAL
   //define caracterÃ­sticas para aparÃªncia do material	
   //exercÃ­cio: testar exemplos da seÃ§Ã£o 
   //Changing Material Properties, do Red Book 
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 30.0 };
          
   glPushAttrib (GL_LIGHTING_BIT);
   
   //atribui caracterÃ­sticas ao material
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
   
   glEnable(GL_LIGHTING);
   //glutSolidTeapot(0.3);
   glScalef(0.5,0.5,0.5);
   glPushMatrix();
        glScalef(10.0,10.0,10.0);
        peixe->desenhar();
   glPopMatrix();
   glDisable(GL_LIGHTING);
   
   glPopAttrib();
}

//função chamada quando a tela é redimensionada 
void Desenho::reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
   
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   
}

//evento que trata clique do mouse
void Desenho::mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            //faz com que a função spinDisplay seja chamada sempre que o 
            //programa estiver ocioso
            glutIdleFunc(NULL);
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            //faz com que nenhuma função seja chamada quando o 
            //programa estiver ocioso
            glutIdleFunc(NULL);
         break;
      default:
         break;
   }
}

// Rotaciona a posição da camera em torno do eixo y
// Exercício: use coordenadas polares para posicionar a câmera em uma esfera ao redor do objeto
void Desenho::specialKeys(int key, int x, int y)
{
   float angulo = 2*M_PI/180;
   switch (key) {
       case GLUT_KEY_LEFT : 
            posCameraX =  posCameraX*cos(-angulo) + posCameraZ*sin(-angulo);
            posCameraZ = -posCameraX*sin(-angulo) + posCameraZ*cos(-angulo);
            break;
       case GLUT_KEY_RIGHT : 
            posCameraX =  posCameraX*cos(angulo) + posCameraZ*sin(angulo);
            posCameraZ = -posCameraX*sin(angulo) + posCameraZ*cos(angulo);                      
            break;          
   }
   glutPostRedisplay();
}
