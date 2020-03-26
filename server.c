#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>


int main(){

    int  sock = (AF_INET,SOCK_STREAM,0);
    printf("%d",sock);


    return 0;
}