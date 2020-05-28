#include "msg.h"
int create_socket();
int start();
int stop();
int status();
void* Func(void* data);
int create_thread(int *csock);
int func_log(char* log);
static void clean (char *chaine);
static void purger(void);
int check_username(int sock,char* buffer);
int check_password(int sock,char* buffer);
int register_account(int sock,paquet* buffer);