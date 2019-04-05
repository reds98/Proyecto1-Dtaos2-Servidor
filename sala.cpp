#include "Socket.h"
#include "sala.h"

using namespace std;
void sala::run()
{
    qDebug()<<"INCIANDO TURNOS";
    Socket  *canal= &Socket::getInstance();

    for (int i=0;i<total_de_jugadores;i++){
        string jsontmp=traductor.SerializarRespuestaUnirseSala(Fichas_Totales->fichas_turno(7),i,puerto,total_de_jugadores);
        qDebug()<<"JASON PARA INICIAR JUEGO: "<<jsontmp.c_str();
        canal->enviar2(jsontmp,8082,Jugadores[i]);
    }
    qDebug()<<"INICIO DE PARTIDA";
    for (int i=0;i<total_de_jugadores;i++){
        qDebug()<<Jugadores[i].c_str();
    }
    ultimo_jugador=0;
    canal->escuchar_partida2(puerto,this);
}

Tablero_Servidor* sala::getTablero()
{
    return Tablero;
}

sala::sala(int porto,int cantidad_de_jugadores)
{
Tablero=new Tablero_Servidor ();
total_de_jugadores=cantidad_de_jugadores;
puerto=porto;
Fichas_Totales=new Bolsa ();
}

void sala::agregar_jugador(string ip,string nombre)
{
    Jugadores[ultimo_jugador]=ip;
    Nombres[ultimo_jugador]=nombre;
    ultimo_jugador++;
    if (ultimo_jugador==total_de_jugadores){
        this->start();
    }
}


void sala::empezar()
{
    this->start();
}

bool sala::Hay_campos()
{
    if (ultimo_jugador==total_de_jugadores){
        return false;
    }
    else{
        return true;
    }
}

Bolsa *sala::getBolsa()
{
    return Fichas_Totales;
}

void sala::ResponderResto(string jason)
{
    Socket  *canal= &Socket::getInstance();
    for (int i=0;i<total_de_jugadores;i++){
        if (i!=ultimo_jugador){
            qDebug()<<"JASON PARTIDA GENERAL ENVIADO: "<<jason.c_str();
            canal->enviar2(jason,8083,Jugadores[i]);
        }
    }
    ultimo_jugador++;
    if (ultimo_jugador>=total_de_jugadores) ultimo_jugador=0;
}

void sala::SumarPuntaje(int puntos)
{

}
