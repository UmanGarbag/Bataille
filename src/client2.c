#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>


#include "client.h"
#define PORT 4001
#define closesocket(s) close(s)
#define SOCKET_ERROR -1
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;


int main(){
        connection();

        return EXIT_SUCCESS;
}

int connection(){

    int sock;
    SOCKADDR_IN sin;
    int erreur = 0;
    int send_to = 0;
    
    if(!erreur)
    {
        /* Création de la socket */
       sock = socket(AF_INET, SOCK_STREAM, 0);

        /* Configuration de la connexion */
        sin.sin_addr.s_addr = inet_addr("127.0.0.1");
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);
 
        /* Si le client arrive à se connecter */
        if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
            printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
        else{
            printf("Impossible de se connecter\n");
        }
        send_data(sock);
        /* On ferme la socket précédemment ouverte */
       // closesocket(sock);

    }

    return EXIT_SUCCESS;

}

int send_data(int sock){

    char phrase[100];
    int envoie;

  // envoie = send(sock,phrase,sizeof(phrase),0);
      /*  
        if(envoie != SOCKET_ERROR){
            printf("Chaine envoyé : %s\n", phrase);
        }
        else
        {
            perror("erreur d'envoie");
        }*/
    char buf[20] = {0};
    
    fd_set readfs;
    int sret;
    struct timeval timeout;
    do
    { 
        FD_ZERO(&readfs);
        FD_SET(sock,&readfs);
        timeout.tv_sec = 5;

        sret = select(sock + 1,&readfs,NULL,NULL,&timeout);
        if (sret > 0)
        {
        //Check dans la socket si il y a une data à send
        recv(sock,buf,sizeof(buf),0); 
        }

        recv(sock,buf,sizeof(buf),0);
        buf[strlen(buf)-1] = 0;
        printf("cli reçoit = %s\n",buf);
        if (!strcmp(buf,"STOP"))
    {
        printf("Je suis dans le break\n");
        break;
    }
        memset(buf,0,sizeof(buf));
        fgets(buf,sizeof(buf),stdin);
        send(sock,buf,sizeof(buf),0);
        memset(buf,0,sizeof(buf));

    } while (1);
    
    return EXIT_SUCCESS;
}

