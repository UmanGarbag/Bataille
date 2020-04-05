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
    
    char username[15];
    char password[26];
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

    while(strlen(password) < 16){
        fgets(password,sizeof(password),stdin);
        printf("Password faible, recommencer");
    }

    if(send(sock,password,sizeof(password),0) != SOCKET_ERROR)
    {
        printf("Password send\n");
    }
    else
    {
        perror("Password don't send");
    }
    
    printf("Compte crée ! Bienvenue %s\n",username);

    while(buf[0] != '1'){
        printf("Taper 1 pour vous connectez ou 3 pour Exit !\n");
        fgets(buf,sizeof(buf),stdin);
        if(strcmp(buf,"1")){
            login();
        }
        else if(strcmp(buf,"3")){
            quit();
        }
    }
    /*Appel de la fonction login, pour après la création du compte se connecters*/
    
    

    
}

int login(int sock){
    char username[200];
    char password[200];

    printf("LOGIN PAGE \n");
    printf("Username: \n");
    fgets(username,sizeof(username),stdin);
    send(sock,username,sizeof(username),0);
    printf("Password: \n");
    fgets(password,sizeof(password),stdin);
    send(sock,password,sizeof(password),0);

    printf("Vous êtes maintenant connecté !");
}

int quit(){

}