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
    int taxaCrescimentoPlanta=0;
    int taxaDiminuicaoPeixe=0;
	
	char lixo[7]="lixo";
	
	FILE *arqInput;
	arqInput=fopen(argv[1],"r");
	if(arqInput==NULL){
		printf("Falha no acesso aos arquivos");
		exit(42);
	}
	fscanf(arqInput," %d %d %d\n",&largura,&altura,&comprimento);
	printf(" %d %d %d\n",largura,altura,comprimento);
	
	fscanf(arqInput," %s %d %d\n",&lixo,&qtdPeixe,&taxaDiminuicaoPeixe);
	printf(" %s %d %d\n",lixo,qtdPeixe,taxaDiminuicaoPeixe);
	
	fscanf(arqInput," %s %d %d\n",&lixo,&qtdPlanta, &taxaCrescimentoPlanta);
	printf(" %s %d %d\n",lixo,qtdPlanta, taxaCrescimentoPlanta);
	
	fscanf(arqInput," %s %d",&lixo,&qtdPedra);
	printf(" %s %d",lixo,qtdPedra);
	
	return 0;
}