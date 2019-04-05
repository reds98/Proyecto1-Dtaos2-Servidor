#include "mainwindow.h"
#include <QApplication>
#include "Socket.h"
#include "linkedlist.h"
#include "qdebug.h"
void descomponer_en_palabras(string  palabras_formadas);
int main(int argc, char *argv[])
{
//    struct sockaddr_in address;
//        int sock = 0, valread;
//        struct sockaddr_in serv_addr;
//        char *hello = "Hello from client";
//        char buffer[1024] = {0};
//        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//        {
//            printf("\n Socket creation error \n");
//            return -1;
//        }

//        memset(&serv_addr, '0', sizeof(serv_addr));

//        serv_addr.sin_family = AF_INET;
//        serv_addr.sin_port = htons(8079);

//        // Convert IPv4 and IPv6 addresses from text to binary form
//        if(inet_pton(AF_INET, "192.168.100.9", &serv_addr.sin_addr)<=0)
//        {
//            printf("\nInvalid address/ Address not supported \n");
//            return -1;
//        }

//        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
//        {
//            printf("\nConnection Failed \n");
//            return -1;
//        }
//        send(sock , hello , strlen(hello) , 0 );
//        printf("Hello message sent\n");
//        valread = read( sock , buffer, 1024);
//        printf("%s\n",buffer );
//        return 0;
     Socket  *canal= &Socket::getInstance();
//     canal->enviar2("#",8079,"192.168.100.9");
//    return 0;
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
