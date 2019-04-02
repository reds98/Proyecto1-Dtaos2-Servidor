#include "mainwindow.h"
#include <QApplication>
#include"sala.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
sala *Partida=new sala();
char ip1[] ="192.168.100.18";
char ip2[] ="192.168.100.17";
char ip3[] ="192.168.100.16";
char ip4[] ="192.168.100.15";
Partida->agregar_jugador(ip1);
Partida->agregar_jugador(ip2);
Partida->agregar_jugador(ip3);
Partida->agregar_jugador(ip4);
Partida->agregar_jugador(ip4);
Partida->agregar_jugador(ip4);
    return a.exec();
}
