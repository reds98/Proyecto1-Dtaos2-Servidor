#ifndef SALA_H
#define SALA_H
#include <QThread>

class sala:public QThread
{
private:

    char *Jugadores[4];
    int turno=4;
    QThread hola;
   void run();
public:
    sala();
     void agregar_jugador(char ip[]);
     char Dame_ip(int valor );
     void empezar();
};

#endif // SALA_H
