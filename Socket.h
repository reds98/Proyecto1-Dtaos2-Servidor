#ifndef SOCKET_H
#define SOCKET_H
#include "tablero_servidor.h"
#include"traductorservidor.h"
#include <map>
#include "sala.h"
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
#include "qdebug.h"
#include <QFile>
#define PORT 8080
using namespace std;

class Socket {
private:
    TraductorServidor* traductor =&TraductorServidor::getInstance();
    Socket();
    int codigo_global=100000;
    map<int,sala*> partidas;
    int PuertoSala=8081;
public:
    static Socket & getInstance(){
        static Socket instance;
        return instance;
    }
    /**
     * @brief NuevaPalabra añade nueva palabra al diccionario
     * @param nueva
     */
    void NuevaPalabra(string nueva);
    /**
     * @brief EliminarSala elimina una sala
     * @param codigo
     */
    void EliminarSala (int codigo);
    /**
     * @brief escuchar_sala2 escucha para crear o unirse a salas
     * @param puerto
     */
    void escuchar_sala2(int puerto);
    /**
     * @brief enviar2 envía uuna string cualquiera
     * @param mnsaje
     * @param puerto
     * @param ip
     */
    void enviar2(string mnsaje,int puerto,string ip);
    /**
     * @brief escuchar_partida2 escucha a jugadores dentro de una partida
     * @param puerto
     * @param SalaActual
     */
    void escuchar_partida2(int puerto, sala* SalaActual);
    /**
     * @brief escuchar2 escucha un puerto cualquiera
     * @param puerto
     * @return la string recibida
     */
    string escuchar2(int puerto);
};


#endif //UNTITLED1_SOCKET_H
