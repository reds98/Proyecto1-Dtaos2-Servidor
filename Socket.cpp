#include "Socket.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
#define PORT 8081
using namespace std;
Socket::Socket() {
    int Puerto_prueba=8081;
}

int Socket::enviar(string Mensaje,int puerto) {
    int n = Mensaje.length();
    char char_array[n + 1];
    strcpy(char_array, Mensaje.c_str());
    char *mensaje_enviar=char_array;
    char char_array2[] ="holaafeoil9090oaaaaaaaaaaaaa";
    char *hello = char_array;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(puerto);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = static_cast<int>(read(sock , buffer, 1024));
    // send(sock , hello , strlen(hello) , 0 );
    close(sock);
    printf("%s\n",buffer );
    return 0;
}
void Socket::escuchar(string Mensaje,int puerto) {

    int n = Mensaje.length();
    char char_array[n + 1];
    strcpy(char_array, Mensaje.c_str());
    char *mensaje_enviar=char_array;
    /*for (int i = 0; i < n; i++)
        cout << *(mensaje_enviar+i);*/
    //cout<<*(hello+13)<<endl;
    prueba(mensaje_enviar,puerto);

}
void Socket::prueba(char *mensaje,int puerto) {
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
    // address.sin_port = htons( PORT );
    int puerto1=8081;
    address.sin_port = htons(puerto);

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
    printf("%s\n",buffer );
    send(new_socket , mensaje , strlen(mensaje) , 0 );
    printf("Hello message sent\n");
    close(new_socket);

}



