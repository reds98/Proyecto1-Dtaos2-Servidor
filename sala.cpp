#include "sala.h"
#include <cstring>
#include <iostream>
#include "string"
#include "Socket.h"
using namespace std;
void sala::run()
{
    //aqui iria la logica de la sala
    cout<<"el hilo funciona"<<endl;
    //aqui vammos a empezar a asignar los turno a los jugadores
    int valor=1;//maximo 4 computadoras
    Socket  *canal= &Socket::getInstance();

    while(valor>=0){
    string jason=traductor.SerializarRespuestaUnirseSala(Fichas_Totales->fichas_turno(7),2-valor,puerto);
    canal->enviar(jason,8080,Jugadores[valor]);
    valor=valor-1;
    cout<<'*'<<endl;
    }
    cout<<"termine lindo"<<endl;
}

sala::sala(int porto)
{
puerto=porto;
cout<<"Se creo la sala con el  puerto "<<puerto<<endl;
Fichas_Totales=new Bolsa ();
}

void sala::agregar_jugador(string ip,string nombre)
{

    if (turno!=0){
        Jugadores[2-turno]=ip;
        Nombre[2-turno]=nombre;
        cout<<"Se unio el jugador "<<Jugadores[2-turno]<<endl;
        cout<<"Se unio el nombre "<<Nombre[2-turno]<<endl;
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

bool sala::Hay_campos()
{
    if (turno==0){
        return false;
    }
    else{
        return true;
    }
}

int sala::get_turno()
{
    return turno;
}

int sala::get_puerto()
{
    return puerto;
}
