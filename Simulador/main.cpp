#include "Desenho.h"

int main (int argc, char** argv)
{
	srand((unsigned)time(NULL));
	srand(rand());
	int qtdPeixe=0;
    int qtdPedra=0;
    int qtdPlanta=0;
    int taxaCrescimentoPlanta=0;
    int taxaDiminuicaoPeixe=0;
	int altura=0;  //y     0  2
	int largura=0; //z  0  5
	int comprimento=0;//x 0 3
	
	char lixo[8];
	
	//Para leitura do arquivo basta descomentar o bloco abaixo
	
	FILE *arqInput;
	arqInput=fopen(argv[1],"r");
	if(arqInput==NULL){
		printf("Falha no acesso ao arquivo");
		exit(42);
	}
		
    //inicializar cubo
    //inicializar posicoes de pedras, plantas e peixes
	
	fscanf(arqInput," %d %d %d\n", &largura,&altura,&comprimento);
	fscanf(arqInput," %s %d %d\n",&lixo,&qtdPeixe,&taxaDiminuicaoPeixe);
	fscanf(arqInput," %s %d %d\n",&lixo,&qtdPlanta,	&taxaCrescimentoPlanta);
	printf("%d\n",taxaDiminuicaoPeixe);
	fscanf(arqInput," %s %d",&lixo,&qtdPedra);
	
	Ecossistema::inicializar(comprimento,altura,largura);
	Desenho opengl(argc,argv,comprimento,altura,largura);
	  
    for (int i=0 ; i < qtdPedra; i++) new Pedra();
    for (int i=0 ; i < qtdPlanta; i++) new Planta(taxaCrescimentoPlanta);
	for (int i=0 ; i < qtdPeixe; i++) new Peixe(taxaDiminuicaoPeixe);
	
	glutMainLoop();
}
