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
    string  Nombres[4];
    int Puntajes[4];
    int puerto;
    int TurnoGlobal=0;
    Bolsa *Fichas_Totales;
    Tablero_Servidor* Tablero;
    int total_de_jugadores;
    int ultimo_jugador=0;
    int PasoSucesivo;
    int codigo;

    void run();
    void empezar();
public:
    void AumentarPuerto();
    bool Hay_campos();
    sala(int porto,int cantidad_de_jugadores,int codigo);
    void agregar_jugador(string ip,string nombre);
    void ResponderResto(string jason);
    void SumarPuntaje(int puntos);
    Tablero_Servidor* getTablero();
    Bolsa* getBolsa();
    void print();
    string IncrementarPaso();
    int getCodigo() const;
    void ReiniciarSucesivo();
    int getPuerto() const;
    void setPuerto(int value);
};


#endif // SALA_H
