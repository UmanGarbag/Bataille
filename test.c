#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
int check_in_file(char* buffer);
#define SIZE_BUFFER 16
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


int main() {
 
    char buffer[SIZE_BUFFER] = "samuel";
    check_in_file(buffer);

}   

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