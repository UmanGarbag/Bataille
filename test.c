#include <stdio.h>

void remiseAZero(int * ptr){

   
    for(int i = 0;i < 3;i++){
         *(ptr + i) = 0;
    }

}


int main(){

  int tab[3] = {15, 16, 17};

    for(int i = 0; i < 3; i++){
        printf(" Avant remise à 0 , Valeur de tab %d --> %p\n", *(tab + i),(tab + i));
    }

  remiseAZero(tab);


    for(int i = 0; i < 3; i++){
        printf("Apres remise à 0 Valeur de tab[%d] =  %d --> %p\n",i,*(tab + i),(tab + i));
    }

  return 0;
}

