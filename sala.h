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
    /**
     * @brief Hay_campos busca campos
     * @return true si hay campos
     */
    bool Hay_campos();
    sala(int porto,int cantidad_de_jugadores,int codigo);/**
     * @brief agregar_jugador añade un jugador
     * @param ip
     * @param nombre
     */
    void agregar_jugador(string ip,string nombre);
    /**
     * @brief ResponderResto envia un mensaje a todos los jugadores menos uno
     * @param jason
     */
    void ResponderResto(string jason);
    /**
     * @brief SumarPuntaje añade puntaje al ultimo jugador
     * @param puntos
     */
    void SumarPuntaje(int puntos);
    /**
     * @brief print imprime valores clave de los jugadores
     */
    void print();
    Tablero_Servidor* getTablero();
    Bolsa* getBolsa();
    string IncrementarPaso();
    int getCodigo() const;
    void ReiniciarSucesivo();
    int getPuerto() const;
    void setPuerto(int value);
};


#endif // SALA_H
