#include "CCamera.h"

Vetor3d setVetor (GLfloat x, GLfloat y, GLfloat z)
{
	Vetor3d temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;
	return temp;
}

void somaVetorAVetor (Vetor3d * destino, Vetor3d * v)
{
	destino->x += v->x;
	destino->y += v->y;
	destino->z += v->z;	
}

CCamera::CCamera()
{
	Posicao = setVetor(0.0, 0.0, 0.0);
	Direcao = setVetor(0.0 ,0.0, -1.0);
	DirecaoMudou = false;
	//inicializando rotacoes
	RotatedX = RotatedY = RotatedZ = 0.0;
}

Vetor3d CCamera::GetPosicao(){
	return Posicao;
}

void CCamera::GetDirecao()
{
	Vetor3d Passo1, Passo2;
	//Normaliza o angulo Y e rotaciona em volta do eixo Y:
	Passo1.x = cos( (RotatedY + 90.0) * M_PI / 180);
	Passo1.z = -sin( (RotatedY + 90.0) * M_PI / 180);
	//Normaliza o angulo Y e rotaciona em volta do eixo X:
	double cosX = cos (RotatedX * M_PI / 180);
	Passo2.x = Passo1.x * cosX;
	Passo2.z = Passo1.z * cosX;
	Passo2.y = sin(RotatedX * M_PI / 180);
	//Sem rotação em Z
	Direcao = Passo2;
	//Todos os valores de direção ficam entre -1 e 1
}

void CCamera::Mover (Vetor3d direcao)
{
	//soma o vetor direção ao vetor posição
	somaVetorAVetor(&Posicao, &direcao);
}

void CCamera::RotacaoX (GLfloat angulo)
{
	RotatedX += angulo;
	DirecaoMudou = true;
}
	
void CCamera::RotacaoY (GLfloat angulo)
{
	RotatedY += angulo;
	DirecaoMudou = true;
}

void CCamera::ParaFrente (GLfloat distancia)
{
	if (DirecaoMudou) GetDirecao();
	Vetor3d VetorMovimento;
	/*multiplica a distância pelo vetor direção que possui
	valores entre -1 e 1 e soma esse vetor ao vetor posição*/
	VetorMovimento.x = Direcao.x * -distancia;
	VetorMovimento.y = Direcao.y * -distancia;
	VetorMovimento.z = Direcao.z * -distancia;
	somaVetorAVetor(&Posicao, &VetorMovimento);
}

void CCamera::ParaOLado (GLfloat distancia)
{
	if (DirecaoMudou) GetDirecao();
	Vetor3d VetorMovimento;
	VetorMovimento.z = -Direcao.x * -distancia;
	VetorMovimento.y = 0.0;
	VetorMovimento.x = Direcao.z * -distancia;
	somaVetorAVetor(&Posicao, &VetorMovimento);
}

void CCamera::Renderizar()
{
	glRotatef(-RotatedX , 1.0, 0.0, 0.0);
	glRotatef(-RotatedY , 0.0, 1.0, 0.0);
	glRotatef(-RotatedZ , 0.0, 0.0, 1.0);
	glTranslatef(-Posicao.x, -Posicao.y, -Posicao.z);
}
