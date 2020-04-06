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
#define MAX_PASSWORD 9
#define closesocket(s) close(s)
#define SOCKET_ERROR -1
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
     //   printf("Fonction connection :  sock == %d\n",sock);
        send_data(sock);
    }

    return EXIT_SUCCESS;

}

int send_data(int sock){

    char buffer[256];
    int envoie;
    int socket = sock;
//  printf("Fonction send_data : socket %d\n",socket);

    printf("Bienvenue au jeu, Bataille Navale !!!\n");
    printf("\n");
    printf("1.Login\n2.Création d'un compte\n3.Exit\n");
    printf("\n");

    /*Récupère la saisie du joueur*/
    fgets(buffer,sizeof(buffer),stdin);
    switch (buffer[0])
    {
    case '1':
        /*FIXME : Appel de la fonction pour ce log*/
        login(sock);
        break;
    case '2':
        /*FIXME : Appel de la fonction pour crée un compte*/
        create_account(sock);
        break;
    case '3':
        /*FIXME : Appel de la fonction qui ferme la connection*/
        quit();
        break;
    default:
        /*FIXME : Appel de la fonction qui envoie le msg d'erreur*/
        break;
    }

    
    
    
    /*envoie = send(sock,buffer,sizeof(buffer),0);
    if(envoie != SOCKET_ERROR){
        printf("Chaine envoyé : %s\n", buffer);
    }
    else
    {
        perror("erreur d'envoie");
    }*/

return EXIT_SUCCESS;
}

int create_account(int sock){
    
    char username[16] = {0};
    char password[16] = {0};
    char buf[200];
    
    printf("Quel sera votre username ? : ");

    fgets(username,sizeof(username),stdin);
    printf("\n");
    
    if(send(sock,username,sizeof(username),0) != SOCKET_ERROR)
    {
        printf("Username send\n");
    }
    else
    {
        perror("Username don't send");
    }
    
    printf("Veuillez choisir un mot de passe :");
    
    fgets(password,sizeof(password),stdin);

    while(strlen(password) < MAX_PASSWORD){
        printf("Password faible, recommencer : ");
        fgets(password,sizeof(password),stdin);
    }

    if(send(sock,password,sizeof(password),0) != SOCKET_ERROR)
    {
        printf("Password send\n");
    }
    else

    {
        perror("Password don't send\n");
    }
    
    printf("Compte crée ! Bienvenue %s\n",username);

    
    do
  {
    memset(buf, 0, 20);
    printf("Taper 1 pour vous connectez ou 3 pour Exit !\n");

    fgets(buf,sizeof(buf),stdin);
    clean(buf);

  
    if(strcmp(buf,"1") == 0){
      login();
      
    }
    else if(strcmp(buf,"3") == 0){
      quit();
    }
    
    }while(*buf != '1' && *buf != '3');
   
    /*Appel de la fonction login, pour après la création du compte se connecters*/
    
}

#define SIZE_BUFFER 16

int login(int sock){
    char username[SIZE_BUFFER];
    char password[SIZE_BUFFER];

    printf("LOGIN PAGE \n");
    printf("Username: \n");
    fgets(username,SIZE_BUFFER,stdin);
    clean(username);
    printf("username = |%s|\n", username);
        if(send(sock,username,SIZE_BUFFER,0) != SOCKET_ERROR){
            printf("Username send\n");
        }
    

    printf("Password: \n");
    fgets(password,SIZE_BUFFER,stdin);
    
    clean(password);
    printf("password = |%s|\n", password);
       if(send(sock,password,SIZE_BUFFER,0) != SOCKET_ERROR){    
            printf("Password send\n");
       }
   
    printf("Vous êtes maintenant connecté !\n");
}

int quit(){
    printf("Au revoir !\n");
    exit(EXIT_SUCCESS);
}