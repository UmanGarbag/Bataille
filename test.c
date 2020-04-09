#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <ncurses.h>
#define SIZE_BUFFER 16
int check_in_file(char* buffer);
  /*   
    int main()
    {
        FILE * Handle = fopen("readtext.txt", "r");
        if(Handle != NULL) {
            char Temp[16];
           // printf("value temp = %s\n taille temp == %d\n",Temp,strlen(Temp));
            int I;
            Temp[3] = 0;
            for(I = 1; I <= 2; I++) {
                fread(Temp,strlen(Temp),1,Handle);
                printf("%i:%s\n",I,Temp);
            }
            fclose(Handle);
        }
        return 0;
    }
*/


int check_in_file(char* buffer){

    //Ouverture fichier
    FILE * credentials;
    char buf[SIZE_BUFFER] = {0};
    credentials = fopen("credentials.txt","r+");
    
    if(credentials != NULL){
        
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

void afficheMot(char * mot){
    char i = 0;
    while(mot[i]!='\0'){
        printf("%c",mot[i]);
        i++;
    }
  /*  while(mot[j] != '\0'){
        printf("%c",mot[j]);
        j++;
    }*/
    printf("\n");
}



#define GRAPH_SIZE 10
int main() {

   char graph[15][15];  
   int i,j;

    for(int i = 0; i < 11; i++)
    {
        for(j = 0; j < 11; j++){
            
            scanf("%c",graph[i][j]);
            printf("i = %d\n j = %d\n",i,j);
    }
    }
    
    /*
    for(i=0;i<10;i++)
    {
        graph[i][i] = '*';
    }

    for(int i = 0; i < 11; i++)
    {
        for(j = 0; j < 11; j++){
            
            printf("%c",graph[i][j]);
        }
        putchar('\n');
    }
    */
    return 0;
} 

int generate_graph(int size){
    return 0;
}