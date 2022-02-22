#ifndef LOGSYSTEM
#define LOGSYSTEM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>   

// function pour creer un user
char createAcc(char *user, char *password);
int checkLogInfo(char *username, char *password);
#endif