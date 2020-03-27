#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "server.h"
#define PORT 4001
#define LOCALHOST 127.0.0.1

int main(){

    int a = create_socket();
    if(a != -1){
        printf("la socket est crée");
    }
    else
        perror("socket");

    return 0;
}

int create_socket()
{
    SOCKADDR_IN sin;
    SOCKET sock;
    socklen_t taille = sizeof(sin);

    SOCKADDR_IN csin;
    SOCKET csock;
    socklen_t crecsize = sizeof(csin);

    int sock;
    int bind_err;
    int ecoute;

    sock = socket(AF_INET,SOCK_STREAM, 0);

    if(sock != -1)
    {
        printf("Socket %d, maintenant ouverte",sock);
        sin.sin_addr.s_addr = htons(INADDR_ANY);
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);
        bind_err = bind(sock, (SOCKADDR*)&sin,taille);

        if(bind_err != -1)
        {
            ecoute = listen(sock,5);
            printf("La socket est en ecoute sur le port %d\n",PORT);

            if(ecoute != -1)
            {
                printf("En attente d'un client");
                csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
                printf("Connection avec la socket %d de %s:%d\n",csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));

            }
            else{
                perror("listen");
            }
        }
        else{
            perror("bind");
            printf("Ferme la socket client\n");
            closesocket(csock);
            closesocket(sock);
        }
    }
    else{
        perror("socket");
    }

    return EXIT_SUCCESS;
}