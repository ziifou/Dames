/*
 * =====================================================================================
 *
 *       Filename:  network.c
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  26/12/2021 12:01:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Khelafi Sif-Eddine (), S-Eddine.KHELAFI@etu.uca.fr
 *   Organization:
 *
 * =====================================================================================
 */
#include "network.h"
#include <stdlib.h>
#include <stdio.h>
#include "./jeu/main.h"
char msg [25];
void spectateur() {
  printf("malheureusement je n'ai pas eu le temps pour l'implémenter :'(  \n");
}


int connectToServ() {
  int socketClient = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addrServer;
  addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
  addrServer.sin_family = AF_INET;
  addrServer.sin_port = htons(50000);

  if ((connect(socketClient, (const struct sockaddr *)&addrServer,
              sizeof(addrServer))) < 0) {
    perror("problem de connextion \n");
    exit(EXIT_FAILURE);
  }
  char serv_response [3];
  recv(socketClient, serv_response, sizeof(serv_response), 0);

  // si la connexion réussit
  if((strcmp(serv_response, "ok")) == 0){
    printf("connected \n\n\n");

    int choix = 0;
  	printf("bienvenue choisit une option \n");
  	printf("1 : creer un compte\n");
  	printf("2 : login\n");
  	printf("3 : le mode spectateur\n");
    scanf("%d", &choix);

    int *pclient = malloc(sizeof(int));
		*pclient = socketClient;
    switch(choix){
		  case 1:;
        //on veut créer un compte
        int choi = 1;
        send(socketClient, &choi, sizeof(int), 0);
		    createAccount(pclient);
		  break;
  		case 2:;
        //on veut login
        send(socketClient, &choix, sizeof(int), 0);

        char username[10];
        char password[10];

        printf("entrez le nom d'utilisateur sans espace \n");
        scanf("%s", username);
        send(socketClient, username, sizeof(username), 0);
        
        printf("entrer le mot de passe sans espace \n");
        scanf("%s", password);
        send(socketClient, password, sizeof(password), 0);

  		  // attendre la repense du serveur
        int log = 0;
        recv(socketClient, &log, sizeof(log), 0);
        if(log){
          startgame(socketClient, username);  
        }else
          printf("fausses informations \n");


  			break;
  		case 3:
  			spectateur();
  			break;
  		default:
			exit(EXIT_SUCCESS);

	  } 
  }else{
    printf("problème survient essayez plus tard... \n");
  }
  
}

struct UserInfo {
		char name[10]; 
		char password[10]; 
};


void createAccount(int *socketCliente) {
  int socketClient = *((int *)socketCliente);

	struct UserInfo user;
  printf("entrez le nom d'utilisateur sans espace \n");
  scanf("%s", user.name);
  send(socketClient, &user.name, sizeof(user.name), 0);
  
  recv(socketClient, msg, sizeof(msg), 0);
  printf("%s\n",msg);
 	scanf("%s", user.password);

  send(socketClient, &user.password, sizeof(user.password), 0);
  

	close(socketClient);
}



void startgame(int socketClient, char *myname){
    printf("choisi un joueur ou taper 99 attend...\n");
    char users[20];
    int i =0;
    char stop[10];
    strcpy(stop, "425#45#");

    while(1){
      recv(socketClient, users, sizeof(users), 0);
      if( (strcmp(users, myname) == 0))
        continue;
      else if( (strcmp(users, stop) == 0) ) 
        break;
      printf("pour jouer avec %s taper %d \n", users, i++);
    }

    scanf("%d", &i);
    send(socketClient, &i, sizeof(i), 0);
    int lance = 0;
    recv(socketClient, &lance, sizeof(lance), 0);
    printf("%d", lance);
    if(lance != 1){
      recv(socketClient, &lance, sizeof(lance), 0);
    }
    if(lance){
        pthread_t threadid;
        pthread_create(&threadid, NULL, 
        lunchGame, socketClient);
        pthread_join(threadid, NULL);

    }
}