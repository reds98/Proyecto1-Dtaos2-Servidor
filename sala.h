#ifndef SALA_H
#define SALA_H
#include <QThread>
#include "string"
#include <string>
#include <iostream>
#include "traductorservidor.h"
using namespace std;
class sala:public QThread
{
private:
  TraductorServidor traductor =TraductorServidor::getInstance();
    string  Jugadores[2];
    string  Nombre[2];
    int turno=2;
    QThread hola;
    int puerto;
   void run();
public:
    sala(int porto);
     void agregar_jugador(string ip,string nombre);
     string Dame_ip(int valor );
     void empezar();
     bool Hay_campos();
     int get_turno();
     int get_puerto();

};


#endif // SALA_H
