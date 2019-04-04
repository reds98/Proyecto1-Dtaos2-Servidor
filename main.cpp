#include "mainwindow.h"
#include <QApplication>
#include "Socket.h"
#include "linkedlist.h"
#include "qdebug.h"
void descomponer_en_palabras(string  palabras_formadas);
int main(int argc, char *argv[])
{
     Socket  *canal= &Socket::getInstance();
     qDebug()<<"Se inicia el servidor";
    canal->escuchar_sala2(8080);
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
