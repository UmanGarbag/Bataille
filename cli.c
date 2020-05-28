#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

#include "msg.h"
#include "client.h"
#define paquet_size sizeof(paquet)
#define PORT 4001
#define MAX_PASSWORD 9
#define SIZE_BUFFER 16
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
    paquet connect = {0};
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
}

int login(int sock){

    paquet credentials = {0};
    paquet pitbull= {0};

    printf("LOGIN PAGE \n");
    printf("Username: ");
    
    fgets(credentials.login,paquet_size,stdin);
    clean(credentials.login);

    printf("username = |%s|\n", credentials.login);
        
    printf("Password: ");

    fgets(credentials.password,paquet_size,stdin);
    clean(credentials.password);

    printf("password = |%s|\n", credentials.password);
    
    printf("\n");
    credentials.message = cred;
    if(send(sock,&credentials,paquet_size,0) != SOCKET_ERROR)
    {
        printf("Username send\n");
    }
    else
    {
        perror("Username don't send");
    }
    char saisie[10];
    if(recv(sock,&pitbull, paquet_size, 0) != SOCKET_ERROR){
        if (pitbull.message == loginok)
        {
            printf("Connecté, bienvenue %s\n",credentials.login);
        }
        else if (pitbull.message == loginKO)
        {
            printf("Aucun compte avec ce username\n");
            printf("\n");
            printf("Voulez-vous créer un compte ? [Y/N]: ");
            fgets(saisie,sizeof(saisie),stdin);
                clean(saisie);
            if (saisie[0] == 'N')
            {
                quit();
            }    
            if (saisie[0] == 'Y')
            {
                create_account(sock);
            }
        }
    }

  
}

int create_account(int sock){
    
   
    char buf[200];
    paquet username = {0};
    
    printf("Quel sera votre username ? : ");

    fgets(username.login,sizeof(username.login),stdin);

    printf("Quel sera votre mot de passe ? : ");

    fgets(username.password,sizeof(username.password),stdin);

    printf("\n");
    username.message = account;
    if(send(sock,&username,sizeof(username),0) != SOCKET_ERROR)
    {
        printf("credentials send\n");
    }
    else
    {
        perror("credentials don't send");
    }
}

int quit(){
    printf("Au revoir !\n");
    exit(EXIT_SUCCESS);
}