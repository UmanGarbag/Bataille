#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>
#include <sys/select.h>
#include "server.h"


#define SOCKET_ERROR -1
#define PORT 4001

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;


int main(int argc, char **argv) {

    if(argc != 2) {
        goto error;
    }

    if(!strcmp(argv[1], "start")){
        /*Lancement du serveur*/
        return start();
    }if(!strcmp(argv[1], "stop")) {
        /*Arret du serveur*/
        return stop();
    }
/*  if(!strcmp(argv[1], "status")) {
        //Affichage statut du serveur
        return status();
    }
*/
    else {
        goto error;
    }

    return EXIT_SUCCESS;

error:
    fprintf(stderr, "%s: invalid arguments\n", argv[0]);
    return EXIT_FAILURE;
}

int start(void){

    printf("Server starting");
    for(int i = 0;i < 3;i++)
        {
        printf(".");
        fflush(stdout);
        sleep(1);
        }
    printf("\n");
    /* Appel de la fonction qui permet de crée une socket*/
    create_socket();
}

int stop(void){
    printf("Stopping the server\n");
     /*Coté lorsque "STOP" est taper le serveur ce stop */
}

int status(void){
    // Je sais pas encore comment faires
}

int create_socket()
{
   SOCKADDR_IN sin; // serveur
   SOCKADDR_IN csin; // client
   socklen_t crecsize = sizeof(csin);
   int sock = 0;
   
   /*Création d'un socket TCP/IP*/
   sock = socket(AF_INET, SOCK_STREAM, 0); 
   
   /*Si la valeur de return de la socket est différent de -1*/
   if(sock != SOCKET_ERROR)
   {
        printf("Socket %d, open\n",sock);

        sin.sin_addr.s_addr = htons(INADDR_ANY);
        sin.sin_family = AF_INET;                 
        sin.sin_port = htons(PORT);  

        int binded = 0;

        /*Ajout de l'IP à la socket*/
        binded = bind(sock,(SOCKADDR*)&sin, sizeof(sin));
   
        if(binded != SOCKET_ERROR)
        {
            int listening;
            /*Mise en état d'écoute de la socket, avec un maximal de connexion définit à 5*/
            listening = listen(sock,5);

        if(listening != SOCKET_ERROR)
            {
            printf("Waiting for a client on %d port\n",PORT);
            }
        }
        /*Boucle infinie qui accepte toutes les connexions*/
        while (1)
        {
            /*Création d'un espace mémoire spécific pour chaque joueur*/
            int *csock = malloc(sizeof(int));

            /*Le serveur accepte la connexion des clients*/
            *csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
            if (*csock == SOCKET_ERROR)
            {
                perror("accept");
            }
            /*FIXME : Renvoyé les messages dans un fichier de log avec la date + heure*/
            else
            {
                printf("Le client est bien connecté, socket n°%d\n",*csock);

            }
            printf("Client connecté socket n°%d\n",*csock);
            
            /*Appel de notre fonction qui crée un thread */
            create_thread(csock);        
        }
   } 
        
    return EXIT_SUCCESS;    
}

/*Fonction appeler par notre thread, le param data == valeur de la socket*/

void* Func(void* data)
{
    int *sock = (int*)data;
    char buffer[256] = {0};
    int login;
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

    /*Boucle infinie qui attend de recevoir de la data*/
    while(1)
    {
        if(recv(*sock,buffer,sizeof(buffer),0) != SOCKET_ERROR)
        {

        }
        else
        {
            perror("recv");
        }
        
    }

    /*On libére l'espace mémoire du malloc pour la socket*/
    free(sock);
    
    /*Arret du thread*/
    pthread_exit(NULL);
    
}  
    
int create_thread(int *csock){

    /*Création d'une variable pour notre thread */

    pthread_t thread1; 

    int pthread_err;

    /*Création de notre thread, avec comme params: notre thread, NULL, Func(fonction à executé par le thread), notre socket*/

    pthread_err = pthread_create(&thread1, NULL, Func, (void *)csock);
    if (pthread_err == -1)
    {
        perror("thread create cancel");
    }
    else
    {
        printf("thread n°%d create\n",pthread_err);
    }

}

int login(){

}

int create_account(){
    
}