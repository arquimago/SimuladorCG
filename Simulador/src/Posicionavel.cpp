#include "Posicionavel.h"

Posicionavel::Posicionavel(char c)
{
   this->tipo= c;//ctor
}

char Posicionavel::getTipo()
{
   return this->tipo;
}

int Planta::sangrar()
{

    return this->diminuir(75);
}

int Planta::diminuir(int massaPerdida)
{

    if (massaPerdida < this->massa)
    {
        this->massa = this->massa - massaPerdida;
        return massaPerdida;
    }
    else
    {
        this->morrer();
        return this->massa;
    }
}

void Planta::morrer ()
{

}

bool Planta::explodir()
{

}

void Planta::crescer()
{
    this->massa = this->massa + this->taxa;
    if (this->massa > 1000)
        this->explodir();
}
