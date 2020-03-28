#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "server.h"


#define SOCKET_ERROR -1
#define PORT 4001

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;


int main(int argc, char **argv) {

    
    if(argc != 2) {
        goto error;
    }

    if(!strcmp(argv[1], "start")) {
        return start();
    }if(!strcmp(argv[1], "stop")) {
        return stop();
    }
  /*  if(!strcmp(argv[1], "status")) {
        return status();
    }*/

    else {
        goto error;
    }

    return EXIT_SUCCESS;

error:
    fprintf(stderr, "%s: invalid arguments\n", argv[0]);
    return EXIT_FAILURE;
}

int start(void){
    printf("Server starting :\n");
    create_socket();
    // FIX ME 
}

int stop(void){
    printf("Stopping the server\n");
     /*Close la socket puis quit le serv */
}

int status(void){
    // FIX ME
}

int create_socket()
{
   SOCKADDR_IN sin; // serveur
   SOCKADDR_IN csin; // client
   socklen_t crecsize = sizeof(csin);
   int sock = 0;
   sock = socket(AF_INET, SOCK_STREAM, 0); // TCP/IP
   
   if(sock != SOCKET_ERROR)
   {
        printf("Socket %d, open",sock);

        sin.sin_addr.s_addr = htons(INADDR_ANY);
        sin.sin_family = AF_INET;                 
        sin.sin_port = htons(PORT);  

        int binded = 0;
        binded = bind(sock,(SOCKADDR*)&sin, sizeof(sin));

    if(binded != SOCKET_ERROR)
    {
        int listening;
        listening = listen(sock,5);

        if(listening != SOCKET_ERROR)
        {
            printf("Waiting for a client on %d port",PORT);
            int csock = 0;
            csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
             
            printf("A client is now connected on %d socket", csock);
        }
        else{
            perror("listen");
            }
    }
    else{
        perror("bind");
        }
  }
   else{
      perror("socket");
        }

    return EXIT_SUCCESS;    
}