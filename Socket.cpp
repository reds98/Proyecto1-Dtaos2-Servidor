#include "Socket.h"

Socket::Socket() {
}

void Socket::NuevaPalabra(string nueva)
{
    QFile file("qrc:/txt/words_alpha.txt");
    if (!file.exists()){
        qDebug()<<"Error, no existe el archivo";
    }
    else{
        file.open(QFile::Append);
        QString nuevaP = QString::fromStdString (nueva);
        QTextStream stream(&file);
        stream << nuevaP << endl;
        file.close();
    }

}

void Socket::EliminarSala(int codigo)
{

}

void Socket::escuchar_sala2(int puerto)
{
        int server_fd, new_socket, valread;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        char buffer[1024] = {0};
        char *hello = "Hello from server";

        // Creating socket file descriptor
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                      &opt, sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons( puerto );

        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr *)&address,
                                     sizeof(address))<0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        while ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t*)&addrlen))>=0)
        {
            memset(buffer,0,1024);

            valread = read( new_socket , buffer, 1024);

            string peticion=  string(buffer);
            qDebug()<<"JASON PARA SALAS: "<<buffer;
            int id=traductor->getID(peticion);

            if (id==0){
                string nombre="";
                string ip="";
                int tsala=0;
                traductor->DeserializarCrearSala(peticion,&ip,&nombre,&tsala);

                sala * sala1= new sala(PuertoSala,tsala,codigo_global);
                sala1->agregar_jugador(ip,nombre);
                partidas.insert(make_pair(codigo_global,sala1));

                string respuesta=traductor->SerializarRespuestaCrearSala(codigo_global);
                qDebug()<<"JASON RESPONDIDO: "<<respuesta.c_str();
                send(new_socket , respuesta.c_str() , strlen(respuesta.c_str()) , 0 );

                PuertoSala+=2;
                codigo_global++;

            }
            else if(id==1){
                string nombre="";
                string ip="";
                int codigo=0;
                traductor->DeserializarUnirseSala(peticion,&ip,&nombre,&codigo);

                string respuesta;
                if (partidas[codigo]==0){
                    respuesta="0";
                }
                else if (partidas[codigo]->Hay_campos()){
                     partidas[codigo]->agregar_jugador(ip,nombre);
                     respuesta="1";

                }
                else{
                     respuesta="2";
                }
                qDebug()<<"JASON RESPONDIDO: "<<respuesta.c_str();
                send(new_socket , respuesta.c_str() , strlen(respuesta.c_str()) , 0 );
            }
            //close(server_fd);
        }

}

void Socket::enviar2(string mensaje, int puerto, string ip)
{
    struct sockaddr_in address;
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char hello[mensaje.length()+1];
        strcpy(hello,mensaje.c_str());
        char buffer[1024] = {0};
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
        }

        memset(&serv_addr, '0', sizeof(serv_addr));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(puerto);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr)<=0)
        {
            printf("\nInvalid address/ Address not supported \n");
        }
        qDebug()<<"JSON HACIA:"<<ip.c_str()<<puerto;

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
        }
        send(sock , hello , strlen(hello) , 0 );
        qDebug()<<"JSON ENVIADO A:"<<ip.c_str()<<puerto<<hello;
}

void Socket::escuchar_partida2(int puerto, sala *SalaActual)
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server2";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( puerto );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    qDebug()<<"PRE ESCUCHAR";
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen))>=0)
    {
        memset(buffer,0,1024);

        valread = read( new_socket , buffer, 1024);

        string FichasJugadas=  string(buffer);
        qDebug()<<"JASON ENTRANTE PARTIDA: "<<buffer;

        Tablero_Servidor* TS=SalaActual->getTablero();
        TraductorServidor* Trad=&TraductorServidor::getInstance();
        qDebug()<<"&&&";
        TS->Desempaquetar(FichasJugadas);
        string RespuestaPrincipal=TS->LeerPalabras(SalaActual->getBolsa());
        qDebug()<<"JSON RESPUESTA PRINCIPAL: "<<RespuestaPrincipal.c_str();

        if (RespuestaPrincipal==""){
            string ganador="";
            ganador=SalaActual->IncrementarPaso();
            if (ganador==""){
                RespuestaPrincipal="1";
                send(new_socket , RespuestaPrincipal.c_str() , strlen(RespuestaPrincipal.c_str()) , 0 );
                string RespuestaGeneral=Trad->SerializarRespuestaTurnoAjeno(buffer,"");
                SalaActual->ResponderResto(RespuestaGeneral);
                 close(server_fd);
                return;
            }
            else{
                qDebug()<<"FIN DEL JUEGO POR PASOS";
                string json="";
                json=Trad->SerializarRespuestaTurnoPropio(false,false,0,ganador,"");
                send(new_socket , json.c_str() , strlen(json.c_str()) , 0 );
                json=Trad->SerializarRespuestaTurnoAjeno(buffer,ganador);
                SalaActual->ResponderResto(json);
                EliminarSala(SalaActual->getCodigo());
                 close(server_fd);
                return;
            }
        }

        bool val;
        val=Trad->getval(RespuestaPrincipal);
        SalaActual->ReiniciarSucesivo();

        if (val){
            string RespuestaGeneral=Trad->SerializarRespuestaTurnoAjeno(buffer,"");
            int puntos=Trad->getPuntos(RespuestaPrincipal);
            SalaActual->SumarPuntaje(puntos);
            SalaActual->ResponderResto(RespuestaGeneral);
            send(new_socket , RespuestaPrincipal.c_str() , strlen(RespuestaPrincipal.c_str()) , 0 );
        }
        else{
            RespuestaPrincipal=Trad->setHayfichas(RespuestaPrincipal,true);
            send(new_socket , RespuestaPrincipal.c_str() , strlen(RespuestaPrincipal.c_str()) , 0 );
            qDebug()<<"PUERTO ESCUCHAR NUEVO INTENTO: "<<SalaActual->getPuerto();
            string RespuestaClienteJson=escuchar2(SalaActual->getPuerto());
            string PalabraCliente=Trad->getPalabra(RespuestaClienteJson);
            qDebug()<<"JSON ENTRANTE TURNO FALLIDO: "<<RespuestaClienteJson.c_str();
            if(PalabraCliente!=""){
                    enviar2(PalabraCliente,8080,"192.168.100.8");
                    string confirmacion=escuchar2(8079);
                    qDebug()<<confirmacion.c_str();
                    //NuevaPalabra(PalabraCliente);
            }
        }

        qDebug()<<"JASON PARTIDA ENVIADO: "<<RespuestaPrincipal.c_str();


    }
     close(server_fd);
}

string Socket::escuchar2(int puerto)
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( puerto );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read( new_socket , buffer, 1024);
    close(server_fd);
    return buffer;
}
