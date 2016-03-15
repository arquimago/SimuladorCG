#include "Posicionavel.h"

/*Posicionavel::Posicionavel()
{
    //ctor
}

Posicionavel::~Posicionavel()
{
    //dtor
}*/

Posicionavel::Posicionavel(char c)
{
   tipo= c;//ctor
}

char Posicionavel::getTipo()
{
   return tipo;
}
