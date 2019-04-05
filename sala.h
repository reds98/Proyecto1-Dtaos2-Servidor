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
    TraductorServidor traductor =TraductorServidor::getInstance();
    string  Jugadores[4];
    string  Nombre[4];
    int Puntajes[4];
    int puerto;
    Bolsa *Fichas_Totales;
    Tablero_Servidor* Tablero;
    int total_de_jugadores;
    int ultimo_jugador=0;

    void run();
    void empezar();
public:
    bool Hay_campos();
    sala(int porto,int cantidad_de_jugadores);
    void agregar_jugador(string ip,string nombre);
    void ResponderResto(string jason);
    Tablero_Servidor* getTablero();
    Bolsa* getBolsa();
};


#endif // SALA_H
