#include "mainwindow.h"
#include <QApplication>
#include "Socket.h"

int main(int argc, char *argv[])
{
    Socket  *canal= &Socket::getInstance();


        string mensaje="si escuche";
        cout<<"escuche bro"<<endl;
        canal->escuchar_sala(mensaje,8080,"");

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
       return 0;
}
