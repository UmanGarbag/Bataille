#ifndef MSG_H
#define MSG_H

typedef 
struct paquet
{
    int message;
    char login[12];
    char password[12];
    char deblanc[12];
    char gy[12]

}paquet;
#define loginok 1
#define loginKO 2
#define account 3 // fonction create_account
#define cred 4 // fonction login


#endif
