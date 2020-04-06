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
#include <time.h>
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
   int returnCode;

   /*Appel de la structure time_t pour avoir l'heure dans les logs*/  
   int h, min, s, day, mois, an;
   time_t now;
   time(&now);
   ctime(&now);

   struct tm *local = localtime(&now);
   h = local->tm_hour;        
   min = local->tm_min;        
   s = local->tm_sec;       
   day = local->tm_mday;          
   mois = local->tm_mon + 1;     
   an = local->tm_year + 1900; 


   /*Création d'un socket TCP/IP*/
   sock = socket(AF_INET, SOCK_STREAM, 0); 
    
   /*Si la valeur de return de la socket est différent de -1*/
   if(sock != SOCKET_ERROR)
   {
        /*Création et ouverture d'un fichier de log*/
        FILE * log_file = fopen("log_server.txt","w");
        
        if(log_file == NULL)
        {
        fprintf(stderr,"Impossible d'ouvrir le fichier");
        exit(-1);
        }

        fprintf(log_file,"%02d/%02d/%d [%02d:%02d:%02d]: Socket %d open\n",day,mois,an,h,min,s,sock);

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
            fprintf(log_file,"%02d/%02d/%d [%02d:%02d:%02d]: Waiting for a client on %d port\n",day,mois,an,h,min,s,PORT);
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
                fprintf(log_file,"%02d/%02d/%d [%02d:%02d:%02d]: Le client est bien connecté, socket n°%d\n",day,mois,an,h,min,s,*csock);

            }
            fprintf(log_file,"%02d/%02d/%d [%02d:%02d:%02d]: Client connecté socket n°%d\n",day,mois,an,h,min,s,*csock);

            /*Fermeture du fichier de log */
            returnCode = fclose(log_file);
             if (returnCode == EOF){
            fprintf( stderr, "Erreur durant la fermeture du fichier" );
            exit( -1 );
            }           
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
    FILE * 
    /*Boucle infinie qui attend de recevoir de la data*/
    while(1)
    {
        if(recv(*sock,buffer,sizeof(buffer),0) != SOCKET_ERROR)
        {
            printf("\n");
            printf("Data reçu %s\n",buffer);
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



