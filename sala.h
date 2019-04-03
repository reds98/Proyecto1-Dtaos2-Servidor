#ifndef SALA_H
#define SALA_H
#include <QThread>
#include "string"
#include <string>
#include <iostream>
#include "traductorservidor.h"
#include "bolsa.h"
using namespace std;
class sala:public QThread
{
private:
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
    sala(int porto,int cantidad_de_jugadores);
     void agregar_jugador(string ip,string nombre);
     string Dame_ip(int valor );
     void empezar();
     bool Hay_campos();
     int get_turno();
     int get_puerto();

};


#endif // SALA_H
