#include "sala.h"
#include <cstring>
#include <iostream>

using namespace std;
void sala::run()
{
    //aqui iria la logica de la sala
    count<<"el hilo funciona"<<endl;
}

sala::sala()
{
    
}

void sala::agregar_jugador(char ip[])
{
    if (turno!=0){
        Jugadores[4-turno]=ip;
        cout<<Jugadores[4-turno]<<endl;
        turno=turno-1;
    }
    else {
        cout<<"ya no queda campo para los demas jugadores"<<endl;
    }
}

char sala::Dame_ip(int valor)
{
    return *Jugadores[valor];
}

void sala::empezar()
{
    this->start();
}
