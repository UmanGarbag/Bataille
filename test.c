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
#include "msg.h"
int check_username(char* buffer);

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

int main(int argc, char const *argv[])
{
    check_username("sam");
    return 0;
}


int check_username(char* buffer){

    //clean(buffer);
    printf("%s\n",buffer);
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
                printf("Connecté, bienvenue %s !\n",buf);
                
            }
        else{
            printf("Aucun compte avec ce username\n");
            }
      }
    }
    
    else {
        perror("fopen");
        return EXIT_FAILURE;
    }
    fclose(credentials);
}