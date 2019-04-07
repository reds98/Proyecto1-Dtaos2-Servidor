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
    int PuertoSala=8080;
public:
    static Socket & getInstance(){
        static Socket instance;
        return instance;
    }
    void NuevaPalabra(string nueva);
    void EliminarSala (int codigo);
    void escuchar_sala2(int puerto);
    void enviar2(string mnsaje,int puerto,string ip);
    void escuchar_partida2(int puerto, sala* SalaActual);
    string escuchar2(int puerto);
};


#endif //UNTITLED1_SOCKET_H
