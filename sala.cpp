#include "sala.h"
#include <cstring>
#include <iostream>
#include "string"
using namespace std;
void sala::run()
{
    //aqui iria la logica de la sala
    cout<<"el hilo funciona"<<endl;
}

sala::sala()
{

}

void sala::agregar_jugador(string ip,string nombre)
{

    if (turno!=0){
        Jugadores[4-turno]=ip;
        Nombre[4-turno]=nombre;
        //cout<<Jugadores[4-turno]<<endl;
        turno=turno-1;
        if(turno==0){
            this->start();
        }
    }
    else {
        cout<<"ya no queda campo para los demas jugadores"<<endl;
    }
}

string sala::Dame_ip(int valor)
{
    return Jugadores[valor];
}

void sala::empezar()
{
    this->start();
}
