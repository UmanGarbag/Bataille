#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
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



    
    int returnCode;
    FILE *file = fopen("destination.txt","w");
    
    if ( file == NULL ) {
        fprintf( stderr, "Erreur durant l'ouverture du fichier" );
        exit( -1 );
    }
    

    fprintf( file, "Date : %02d/%02d/%d, heure :  [%02d:%02d:%02d] ",day,mois,an,h,min,s);
        
    returnCode = fclose(file);
    if ( returnCode == EOF ) {
        fprintf( stderr, "Erreur durant la fermeture du fichier" );
        exit( -1 );
    }
    
    return 0;
}   