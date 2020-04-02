#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
 
void* maFonction(void* data);
 
 
 
int main()
{
    int i;
    
    // On crée un thread
    pthread_t thread;
    
    // Permet d'exécuter le fonction maFonction en parallèle
    pthread_create(&thread, NULL, maFonction, (void*)&i);
 
    // Affiche 50 fois 1
    for(i=0 ; i<50 ; i++)
        printf("1");
 
    // Attend la fin du thread créé
    pthread_join(thread, NULL);
    
    return 0;
}
 
 
void* maFonction(void* data)
{
    int i;
    
    // Affiche 50 fois 2
    for(i=0 ; i<50 ; i++)
        printf("2");
    
    return NULL;
}