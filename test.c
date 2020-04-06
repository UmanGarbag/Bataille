#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
  char buf[20];  
  do
  {
    memset(buf, 0, 20);
    printf("Taper 1 pour vous connectez ou 3 pour Exit !\n");

    fgets(buf,sizeof(buf),stdin);
    clean(buf);

  
    if(strcmp(buf,"1") == 0){
      printf("login\n");
      
    }
    else if(strcmp(buf,"3") == 0){
      printf("quit\n");
    }
    

  }while(*buf != '1' && *buf != '3');
}   