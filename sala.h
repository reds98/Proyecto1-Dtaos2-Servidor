#ifndef SALA_H
#define SALA_H
#include <QThread>
#include "string"
#include <iostream>
#include "traductorservidor.h"
#include "bolsa.h"
#include "tablero_servidor.h"
#include "qdebug.h"
#include <cstring>
#include <iostream>

using namespace std;
class sala:public QThread
{
private:
    Tablero_Servidor *Tablero;
    TraductorServidor traductor =TraductorServidor::getInstance();
    string  Jugadores[4];
    string  Nombre[4];
    int turno;
    QThread hola;
    int puerto;
    Bolsa *Fichas_Totales;
    void run();
    int total_de_jugadores;
public:
     Tablero_Servidor* getTablero();
    sala(int porto,int cantidad_de_jugadores);
     void agregar_jugador(string ip,string nombre);
     string Dame_ip(int valor );
     void empezar();
     bool Hay_campos();
     int get_turno();
     int get_puerto();
     Bolsa* getBolsa();
     void reponder_al_resto(int jugador_actual,string jason);
};


#endif // SALA_H
