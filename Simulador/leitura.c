#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
	
	int qtdPeixe=0;
    int qtdPedra=0;
    int qtdPlanta=0;
    int altura=0;  //y     0  2
    int largura=0; //z  0  5
    int comprimento=0;//x 0 3
    int taxaCrescimentoPlanta=10;
    int taxaDiminuicaoPeixe=819929;
	
	char lixo[7]="lixo";
	
	FILE *arqInput;
	arqInput=fopen(argv[1],"r");
	if(arqInput==NULL){
		printf("Falha no acesso ao arquivo");
		exit(42);
	}
	fscanf(arqInput," %d %d %d", &largura, &altura, &comprimento);
	
	fscanf(arqInput," %s %d %d", &lixo, &qtdPeixe, &taxaDiminuicaoPeixe);
	//Aqui o valor existe
	printf("Taxa de Diminuicao Peixe %d\n",taxaDiminuicaoPeixe);
	
	fscanf(arqInput," %s %d %d", &lixo, &qtdPlanta, &taxaCrescimentoPlanta);
	//fscanf(arqInput," %s %d",&lixo,&qtdPedra);
	
	//Aqui o valor sumiu!!
	printf("Taxa de Diminuicao Peixe %d\n",taxaDiminuicaoPeixe);
	
	return 0;
}