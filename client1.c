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

    /*Appel de la fonction qui permet la connection au servjeu*/
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
        /*Création d'un socket TCP/IP*/
       sock = socket(AF_INET, SOCK_STREAM, 0);

        /* Configuration de la connexion */
        sin.sin_addr.s_addr = inet_addr("127.0.0.1");
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);
 
        /*Connection du client*/
        if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
            printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
        else{
            printf("Impossible de se connecter\n");
        }
        /*Appel de la fonction qui permet d'envoyé de la data*/
        send_data(sock);
    }

    return EXIT_SUCCESS;

}

int send_data(int sock){

    char buffer[256];
    int envoie;

    /*Récupère la saisie du joueur*/
    fgets(buffer,sizeof(buffer),stdin);
    
    printf("Bataille Navale !!!\n");
    printf("1.Login\n 2.Création d'un compte\n 3.Exit");

    fgets(buffer,sizeof(buffer),stdin);
    switch (buffer[0])
    {
    case '1':
        /*FIXME : Appel de la fonction pour ce log*/
        break;
    case '2':
        /*FIXME : Appel de la fonction pour crée un compte*/
        break;
    case '3':
        /*FIXME : Appel de la fonction qui ferme la connection*/
        break;
    default:
        /*FIXME : Appel de la fonction qui envoie le msg d'erreur*/
        break;
    }

    
    
    
        envoie = send(sock,buffer,sizeof(buffer),0);
    if(envoie != SOCKET_ERROR){
        printf("Chaine envoyé : %s\n", buffer);
    }
    else
    {
        perror("erreur d'envoie");
    }

return EXIT_SUCCESS;
}

