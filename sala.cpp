#include "Socket.h"
#include "sala.h"

using namespace std;
int sala::getCodigo() const
{
    return codigo;
}

void sala::run()
{
    qDebug()<<"INCIANDO TURNOS";
    Socket  *canal= &Socket::getInstance();

    for (int i=0;i<total_de_jugadores;i++){
        string jsontmp=traductor.SerializarRespuestaUnirseSala(Fichas_Totales->fichas_turno(7),i,puerto,total_de_jugadores);
        qDebug()<<"JASON PARA INICIAR JUEGO: "<<jsontmp.c_str();
        canal->enviar2(jsontmp,8078,Jugadores[i]);
    }
    qDebug()<<"INICIO DE PARTIDA";
    for (int i=0;i<total_de_jugadores;i++){
        qDebug()<<Jugadores[i].c_str();
    }
    ultimo_jugador=0;
    print();
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

void sala::print()
{
    for (int i=0;i<4;i++){
        cout<<"Jugador: "<<Nombres[i]<<", ";
        cout<<"Puntaje: "<<Puntajes[i]<<", ";
        cout<<"Ip: "<<Jugadores[i]<<endl;
    }
}

string sala::IncrementarPaso()
{
    PasoSucesivo++;
    qDebug()<<"PASO SUCESIVO: "<<PasoSucesivo;
    if (PasoSucesivo==total_de_jugadores){
        int index;
        int mayor=0;
        for (int i;i<4;i++){
            if (Puntajes[i]>mayor){
                mayor=Puntajes[i];
                index=i;
            }
        }
        return Nombres[index];
    }
    return "";
}



void sala::ResponderResto(string jason)
{
    Socket  *canal= &Socket::getInstance();
    PasoSucesivo=0;
    for (int i=0;i<total_de_jugadores;i++){
        if (i!=ultimo_jugador){
            qDebug()<<"JASON PARTIDA GENERAL ENVIADO: "<<jason.c_str();
            canal->enviar2(jason,8080+TurnoGlobal,Jugadores[i]);
        }
    }
    TurnoGlobal++;
    ultimo_jugador++;
    if (ultimo_jugador>=total_de_jugadores){
        ultimo_jugador=0;
        print();
        qDebug()<<"RONDA COMPLETA ";
    }
}

void sala::SumarPuntaje(int puntos)
{
    Puntajes[ultimo_jugador]+=puntos;
}
