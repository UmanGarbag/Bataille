#ifndef MSG_H
#define MSG_H

typedef 
struct paquet
{
    int message;
    char login[12];
    char password[12];

}paquet;
#define loginok 1
#define loginKO 2


#endif
