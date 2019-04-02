#ifndef SALA_H
#define SALA_H
#include <QThread>
#include "string"
#include <string>
#include <iostream>
using namespace std;
class sala:public QThread
{
private:

    string  Jugadores[4];
    string  Nombre[4];
    int turno=4;
    QThread hola;
   void run();
public:
    sala();
     void agregar_jugador(string ip,string nombre);
     string Dame_ip(int valor );
     void empezar();
};

#endif // SALA_H
