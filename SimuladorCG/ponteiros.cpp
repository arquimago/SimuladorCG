#include <iostream>
using namespace std;


class Inteiros
{
   public:
       int valor;




};

void imprimir(Inteiros* a)
{
    cout << a[0].valor << "\n"; //acessa vetor
    cout << a[0,1].valor<< "\n"; //acessa matriz
}

void imprimir2(Inteiros** a)
{
    cout << (*a[0]).valor << "\n"; //acessa o objeto no primeiro ponteiro
    cout << a[0]->valor;       //equivalente

}


int main ()
{
    //teste de ponteiros
    /*
    int* a;
    int b=3;
    a=&b;
    cout << *a;
    cout << a;
    */
    //teste passando referencias para fun��es de ponteiro
    /*
    Inteiros int2;
    int2.valor=1235;
    imprimir(&int2);
    cout << int2.valor;
    */
    //teste de vetores
    /*
    int* a;
    a = new int [3];
    a[2] = 3;
    cout << a[2];
    */
    //matrizes
    /*
    int* a;
    a = new int [3,3];
    a[2,1]=2;
    cout << a[2,1];
    /*/
    //vetores para fun��o
    /*
    Inteiros* int3 = new Inteiros [3];
    imprimir(int3);
    */
    //matrizes para fun��o
    /*
    Inteiros* int3 = new Inteiros [3,1];
    imprimir(int3);
    */

    //teste vetores de ponteiros
    /*
    Inteiros** int1 = new Inteiros*[3]; //vetor de 3 ponteiros
    //inicializa��es
    int1[0]= new Inteiros[1];  // cria na posi��o 1 do vetor um novo vetor de Inteiros, de tamanho 1
    int1[1]= new Inteiros[1]; //etc
    int1[2]= new Inteiros[1]; //etc
    imprimir2(int1);
    */
}
