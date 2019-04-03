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
    int valor=total_de_jugadores-1;//maximo 4 computadoras
    Socket  *canal= &Socket::getInstance();
    while(valor>=0){
    string jason=traductor.SerializarRespuestaUnirseSala(Fichas_Totales->fichas_turno(7),2-valor,puerto,total_de_jugadores);
    canal->enviar(jason,8080,Jugadores[valor]);
    valor=valor-1;
    cout<<'*'<<endl;
    }

    cout<<puerto<<"66677"<<endl;

    while (true) {

        canal->escuchar_partida(puerto,this);

    }
    cout<<" lindo"<<endl;
}

Tablero_Servidor* sala::getTablero()
{
    return Tablero;
}

sala::sala(int porto,int cantidad_de_jugadores)
{
Tablero=new Tablero_Servidor ();
total_de_jugadores=cantidad_de_jugadores;
turno=cantidad_de_jugadores;
puerto=porto;
cout<<"Se creo la sala con el  puerto "<<puerto<<endl;
cout<<"el size de la sala es "<<cantidad_de_jugadores<<endl;
Fichas_Totales=new Bolsa ();
cout<<"cree una bolsa "<<cantidad_de_jugadores<<endl;
}

void sala::agregar_jugador(string ip,string nombre)
{
 //cout<<total_de_jugadores<<"*"<<turno<<endl;
    if (turno!=0){
        Jugadores[total_de_jugadores-turno]=ip;
        Nombre[total_de_jugadores-turno]=nombre;
        cout<<"Se unio el jugador "<<Jugadores[total_de_jugadores-turno]<<endl;
        cout<<"Se unio el nombre "<<Nombre[total_de_jugadores-turno]<<endl;
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

Bolsa *sala::getBolsa()
{
    return Fichas_Totales;
}

void sala::reponder_al_resto(int jugador_actual,string jason)
{
    int valor=total_de_jugadores-1;
    Socket  *canal= &Socket::getInstance();
    while(valor>=0){
        if (valor!=jugador_actual){
        string respuesta=jason;
        canal->enviar(jason,puerto,Jugadores[valor]);
        cout<<'*'<<endl;
        }
        valor=valor-1;
    }
}
