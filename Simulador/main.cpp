#include "Desenho.h"

int main (int argc, char** argv)
{
	//inicializações
	srand((unsigned)time(NULL));
	srand(rand());
	int qtdPeixe = 0;
    int qtdPedra = 0;
    int qtdPlanta = 0;
    int taxaCrescimentoPlanta = 0;
    int taxaDiminuicaoPeixe = 0;
	int altura = 0;  //y     0  2
	int largura = 0; //z  0  5
	int comprimento = 0;//x 0 3
	char lixo[8];
	
	//leitura do arquivo
	FILE *arqInput;
	arqInput=fopen(argv[1],"r");
	if(arqInput==NULL){
		printf("Falha no acesso ao arquivo");
		exit(42);
	}		
	
	fscanf(arqInput," %d %d %d\n", &largura,&altura,&comprimento);
	fscanf(arqInput," %s %d %d\n",&lixo,&qtdPeixe,&taxaDiminuicaoPeixe);
	fscanf(arqInput," %s %d %d\n",&lixo,&qtdPlanta,	&taxaCrescimentoPlanta);
	printf("%d\n",taxaDiminuicaoPeixe);
	fscanf(arqInput," %s %d",&lixo,&qtdPedra);
	
	
	//inicializar cubo
	Ecossistema::inicializar(comprimento,altura,largura);
	
	//inicializar funcionalidades opengl
	Desenho opengl(argc,argv,comprimento,altura,largura);

    //inicializar posicoes de pedras, plantas e peixes	
    for (int i = 0 ; i < qtdPedra; i++) 
		new Pedra();
    for (int i = 0 ; i < qtdPlanta; i++) 
		new Planta(taxaCrescimentoPlanta);
	for (int i = 0 ; i < qtdPeixe; i++) 
		new Peixe(taxaDiminuicaoPeixe);
	
	//chamar main opengl
	glutMainLoop();
}
