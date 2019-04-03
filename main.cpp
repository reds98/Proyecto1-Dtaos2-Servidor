#include "mainwindow.h"
#include <QApplication>
#include "Socket.h"
#include "linkedlist.h"
void descomponer_en_palabras(string  palabras_formadas);
int main(int argc, char *argv[])
{
//    Socket  *canal= &Socket::getInstance();


//        string mensaje="si escuche";
//       // cout<<"escuche bro"<<endl;
//       canal->escuchar_sala(mensaje,8080,"");
//      canal->mapa();
////    QApplication a(argc, argv);
////    MainWindow w;
////    w.show();
      string prueba=",perro,gato,raton,feo,";
      descomponer_en_palabras(prueba);

//    return a.exec();
       return 0;
}
void descomponer_en_palabras(string  palabras_formadas){
    LinkedList *lista_de_palabras=new LinkedList;
    string palabra="";

    for(int i=0 ; i<palabras_formadas.size();i++)
    {
        if(palabras_formadas[i]==','){
            string* valor=new string(palabra);
            lista_de_palabras->Add(valor);//(&palabra);
           //cout<<palabra<<endl;
            palabra="";
        }
        else {
            palabra+=palabras_formadas[i];
        }
    }
  cout<<*(string *)lista_de_palabras->getFirst()->getNext()->getNext()->getData()<<endl;

};
