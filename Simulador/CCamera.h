#ifndef CCAMERA_H
#define CCAMERA_H


#include "GL/glut.h"
#include "math.h"

struct Vetor3d  //Vetor 3D de floats
{
	GLfloat x,y,z;
};

class CCamera
{
	private:
		Vetor3d Posicao;
		Vetor3d Direcao;		/*Not used for rendering the camera, but for "moveforwards"
								So it is not necessary to "actualize" it always. It is only
								actualized when ViewDirChanged is true and moveforwards is called*/
		bool DirecaoMudou;
		GLfloat RotatedX, RotatedY, RotatedZ;	
		void GetDirecao ();
	public:
		CCamera();			//inits the values (Position: (0|0|0) Target: (0|0|-1) )
		void Renderizar ();	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render
		void Mover ( Vetor3d Direction );
		void RotacaoX ( GLfloat Angle );
		void RotacaoY ( GLfloat Angle );
		void ParaFrente ( GLfloat Distance );
		void ParaOLado ( GLfloat Distance );
		Vetor3d GetPosicao();
};

Vetor3d setVetor ( GLfloat x, GLfloat y, GLfloat z );
void somaVetorAVetor ( Vetor3d * Dst, Vetor3d * V2);

#endif