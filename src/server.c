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
#include "msg.h"


#define SOCKET_ERROR -1
#define PORT 4001
#define SIZE_BUFFER 16
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

static void purger(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {}
}

static void clean (char *chaine)
{
    char *p = strchr(chaine, '\n');

    if (p)
    {
        *p = 0;
    }

    else
    {
        purger();
    }
}


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
        /*Création et ouverture d'un fichier de log*/
        char buffer[2048];

        sprintf(buffer,"Socket %d open\0",sock);
        func_log(buffer);

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
               sprintf(buffer," Waiting for a client on %d port\n",PORT);
               func_log(buffer);
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
                sprintf(buffer," Le client est bien connecté, socket n°%d\n",*csock);
                func_log(buffer);
            }
                sprintf(buffer,"Client connecté, socket n°%d\n",*csock);
                func_log(buffer);
            
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
    char  buffer[SIZE_BUFFER] = {0};
    char  buffer2[SIZE_BUFFER] = {0};          
  
    /*if(credentials == NULL){
        pthread_exit(NULL);
    }*/
    /*Boucle infinie qui attend de recevoir de la data*/
    int i = 0;
    
    while (1)
    {
         paquet data = {0};
        if (recv(*sock,&data,sizeof(paquet),0) < 1)
        {
            /*Ferme le thread si le serv si le client se deco*/
            pthread_exit(NULL);
        }
        else
        {            
            //clean(data.login);
            //clean(data.password);
            //printf("data.login = %s || data.password = %s\n",data.login,data.password);
            check_username(*sock,data.login);
            
                
            
            
            
            
        }
            
    }
        
     
    
    


/*
    while(i < 6)
    {
       // memset(buffer, 0, SIZE_BUFFER);
        if(recv(*sock, buffer, SIZE_BUFFER, 0) != SOCKET_ERROR){
            check_in_file(*sock,buffer);
            printf("J'ai recu : |%s|\n", buffer);
        }
      
    }
*/
    /*On libére l'espace mémoire du malloc pour la socket*/
    free(sock);
    
    /*Arret du thread*/
    pthread_exit(NULL);
        

     /*if (fclose(credentials) == EOF)
    {
        fprintf( stderr, "Erreur durant la fermeture du fichier" );
        exit(-1);
    }*/
   
    
}


 

int create_thread(int *csock){

    /*Création d'une variable pour notre thread */
    char buffer[2048];
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
        sprintf(buffer,"thread n°%d create\n",pthread_err);
        func_log(buffer);
    }

}
  


int func_log(char* log)
{
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

    FILE* log_file = fopen("log_server.txt","a+");
        
    if(log_file == NULL)
    {
        fprintf(stderr,"Impossible d'ouvrir le fichier");
        return -1;
    }
        
    fprintf(log_file,"%02d/%02d/%d [%02d:%02d:%02d]: %s\n",day,mois,an,h,min,s,log);

    if (fclose(log_file) == EOF)
    {
        fprintf( stderr, "Erreur durant la fermeture du fichier" );
        return -1;
    }

    return 0;
}

int check_username(int sock,char* buffer){

    char buf[SIZE_BUFFER] = {0};

    FILE * credentials;
   
    /*Ouverture du fichier*/
    credentials = fopen("username.txt","r+");
    
    if(credentials != NULL){

    /*------------------------FIXME---------------------------------------------------------------------------------------------------------------------------------------------------------------*/  
      /*Faire deux fichier distincs pour le login et le mot de passe
      Dans la fonction check_in_file rajouter une ouverte de fichier pour le password.txt
      Crée un 2ème buffer dans la fonction Fun(thread main) pour le password le premier etant pour le username
       Surement deux fonctions une int check_username(int sock, char* buffer1) pour verifier le login et une autre check_password(int sock,char *buffer2) pour check le password c plus simple*/  
   /* ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
      
      
        while(fgets(buf,SIZE_BUFFER, credentials) != NULL){
            if(strcmp(buffer,buf) == 0){
                if(send(sock,buf,SIZE_BUFFER,0) != SOCKET_ERROR){
                    printf("Connecté, bienvenue %s !\n",buf);
                }
            }
        else{
            send(sock,buf,SIZE_BUFFER,0) != SOCKET_ERROR;
            printf("Aucun compte avec ce username\n");
        }
      }
    }
    
    else {
        perror("fopen");
        return EXIT_FAILURE;
    }
    fclose(credentials);

    return 0;
}