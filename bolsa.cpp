#include "bolsa.h"
#include <cstdlib>
#include "iostream"
#include <ctime>
#include <array>
using namespace std;
int Bolsa::getCantidad_total() const
{
    return cantidad_total;
}

void Bolsa::setCantidad_total(int value)
{
    cantidad_total = value;
}

string Bolsa::fichas_turno(int numero_de_fichas)
{
   string s;
   int contador=0;
   while (contador<numero_de_fichas){
       s+=agarrar_ficha();
       contador=contador+1;
   }
   return s;
}


Bolsa::Bolsa()
{
    srand((int)time(0));//manera que el rand detecta que es que
}

char Bolsa::agarrar_ficha_aux(int r )
{
    if (cantidad[r]>0){
        cantidad[r]=cantidad[r]-1;
        cantidad_total=cantidad_total-1;
       return letras[r];
    }
    else if(r<27){
        return agarrar_ficha_aux(r+1);
    }

}

char Bolsa::agarrar_ficha()
{
    int r = (rand() % 26) + 1;;
    if (cantidad[r]>0){
        cantidad[r]=cantidad[r]-1;
        cantidad_total=cantidad_total-1;
       return letras[r];
    }
    else if (cantidad_total>0){
        return agarrar_ficha_aux(0);
    }
    else{
        return '0';//este caso es cuando no hay mas fichas en la bolsa entonces se devuelve este char signifancos que no hay mas fichas
    }

}

char Bolsa::prueba(int letra)
{

char valor=letras[letra];
return valor;
}

void Bolsa::poner_cero()
{
    int valor=0;
    while(valor!=27){
     cantidad[valor]=0;
     valor=valor+1;
    }

}

int Bolsa::contar_cantidad()
{
    int total=0;
    int valor=0;
    while(valor!=27){
     total=cantidad[valor]+total;
     valor=valor+1;
    }
    return total;

}

