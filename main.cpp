#include "mainwindow.h"
#include <QApplication>
#include "Socket.h"

int main(int argc, char *argv[])
{
    Socket  *canal= &Socket::getInstance();
    while(true){
        string mensaje="si escuche";
        canal->escuchar_sala(mensaje,8080,"");
    }
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
       return 0;
}
