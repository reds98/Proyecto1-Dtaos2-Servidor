#ifndef SALA_H
#define SALA_H


class sala
{
private:

    char *Jugadores[4];
    int turno=4;
public:
    sala();
     void agregar_jugador(char ip[]);
     char Dame_ip(int valor );
};

#endif // SALA_H
