#include "logedClients.h"
#include "logsystem.h"
#include "jeu.h"
static struct ClientNetInfo clientsNetInfo [MAXCLIENTS];
// client index table info
static int cniI = 0;
pthread_mutex_t lock;


void loged(char *username, int clientSocket){
    //le serveur est PLEIN
    if(clientsNetInfo[cniI].occupe == 1){
        return;
    }
    // mettre les clients dans le tableau
    pthread_mutex_lock(&lock);
      strcpy(clientsNetInfo[cniI].username, username);
      clientsNetInfo[cniI].clientSock = clientSocket;
      clientsNetInfo[cniI].occupe = 1;
      int myindex = cniI;
    pthread_mutex_unlock(&lock);

    sendUsers(clientSocket);

    pthread_mutex_lock(&lock);
    cniI = (cniI +1) % 20;
    pthread_mutex_unlock(&lock);
    // recevoir le choix du client.
    int choix = 0;
    recv(clientSocket, &choix, sizeof(choix),0);
    printf("choix %d \n",choix);
    if(choix == 99){
      int d = 99;
      send(clientSocket, &d, sizeof(d), 0);
    }

    if(clientsNetInfo[choix].occupe == 1){
      // supprimer les clients de la liste d attente
      int client2 =  clientsNetInfo[choix].clientSock;
      clientsNetInfo[choix].occupe = 0;
      clientsNetInfo[myindex].occupe = 0;
      pthread_mutex_lock(&lock);
         cniI -=2;
      pthread_mutex_unlock(&lock);

      lancerPartie(clientSocket, client2);     
    }else
      while(1);
    
    pthread_mutex_destroy(&lock);
    return;
}



void sendUsers(int clientSocket){
    for(int i = 0; i<MAXCLIENTS; i++){
      if(clientsNetInfo[i].occupe != 1)
        break;
      //envoyer la liste des users au clients
      size_t s = sizeof(clientsNetInfo[i].username);
      send(clientSocket, (clientsNetInfo[i].username), s, 0);
      sleep(1);
    }
    // arete
    char stop[10];
    strcpy(stop, "425#45#");
    send(clientSocket, stop, sizeof(stop), 0);
    return;
}

void lancerPartie(int sock1, int sock2){
     // initialiser la connextion
    int lance = 1;
    send(sock1, &lance, sizeof(lance), 0);
    send(sock2, &lance, sizeof(lance), 0);


    // la logique du jeu

    matrixJType matrixJ[8][8]; 
    Positions APositions;
    Positions DPositions;
    Positions click;
    int gameover = 0;
    int turn = vert;
    send(sock1, &turn, sizeof(turn), 0);
    send(sock2, &turn, sizeof(turn), 0); 
    int sockets[2];
    sockets[0] = sock1; //blanc
    sockets[1] = sock2;
    int turnSock = 0;
    int valid = 0;

    initMatrix(matrixJ);

    while (!gameover) {
      int movechoosed = 0;
      int yourturn = 1;
      send(sockets[turnSock], &yourturn, sizeof(yourturn), 0);
      yourturn = 0;
      send(sockets[(turnSock + 1) %2 ], &yourturn, sizeof(yourturn), 0);
      while (!movechoosed) {
          printf("click... \n");
          if((recv(sockets[turnSock], &click, sizeof(click), 0)) <=0){
              close(sock1);
              close(sock2);
              pthread_exit(NULL);
             
          }
         
          printf("j'ai recu la clique...\n");

          if (validDePiece(turn, matrixJ, click)) { 
              DPositions = click; 
              valid =1;

              send(sockets[turnSock], &valid, sizeof(valid),0 );
              printf("valide de joueur %i \n", turnSock);
          }
  
          else if (validAPiece(turn, matrixJ, DPositions, click)) {
              APositions = click;
              movechoosed = 1;

              valid++;
              send(sockets[turnSock], &valid, sizeof(valid),0 );
              printf("valide de joueur %i \n",turnSock);
          }
  
          else if (prendPiece(turn, matrixJ, DPositions, click) == blanc_gauche) {
              APositions = click;
              matrixJ[DPositions.x+1][DPositions.y-1].couleur = UNDEFINED; 
              matrixJ[DPositions.x+1][DPositions.y-1].state = VIDE;
              movechoosed = 1; 
              valid++;
              send(sockets[turnSock], &valid, sizeof(valid),0 );
  
          }
  
          else if (prendPiece(turn, matrixJ, DPositions, click) == blanc_droite) {
  
              APositions = click; 
              matrixJ[DPositions.x +1][DPositions.y+1].couleur = UNDEFINED;
              matrixJ[DPositions.x +1][DPositions.y+1].state = VIDE;
              movechoosed = 1;
              valid++;
              send(sockets[turnSock], &valid, sizeof(valid),0 );
  
          }
  
          else if (prendPiece(turn, matrixJ, DPositions, click) == vert_gauche) {
              APositions = click; 
              matrixJ[DPositions.x-1][DPositions.y-1].couleur = UNDEFINED;
              matrixJ[DPositions.x-1][DPositions.y-1].state = VIDE; 
              movechoosed = 1;
              valid++;
              send(sockets[turnSock], &valid, sizeof(valid),0 );
  
          }
  
          else if (prendPiece(turn, matrixJ, DPositions, click) == vert_droite) {
  
              APositions = click; 
              matrixJ[DPositions.x-1][DPositions.y+1].couleur = UNDEFINED; 
              matrixJ[DPositions.x-1][DPositions.y+1].state = VIDE; 
              movechoosed = 1;
              valid++;
              send(sockets[turnSock], &valid, sizeof(valid),0 );
          }else{
              valid = 0;
              send(sockets[turnSock], &valid, sizeof(valid),0 );
          }
      }
        //update le jeu
        matrixJ[DPositions.x][DPositions.y].state = VIDE;
        matrixJ[DPositions.x][DPositions.y].couleur = UNDEFINED;
    
        matrixJ[APositions.x][APositions.y].state = PLEIN; 
        matrixJ[APositions.x][APositions.y].couleur = turn; 


        // envoyer les données
        for(int i =0; i<2; i++){
          send(sockets[i], &turn, sizeof(int),0);
          send(sockets[i], &matrixJ, sizeof(matrixJ),0);
          send(sockets[i], &DPositions, sizeof(DPositions),0);
          send(sockets[i], &APositions, sizeof(APositions),0);
        }
       
        sleep(1);
        // y a t 'il un gagnant ?
        if (gagner(matrixJ)) {
            gameover = 2; 

            printf("le gagnant est le joueur %i ... \n",turnSock); 

            send(sockets[turnSock], &gameover, sizeof(gameover),0);
            gameover = 3;  
            send(sockets[(turnSock + 1) % 2], &gameover, sizeof(gameover),0);
            
        }

        else {
            gameover = 0; 
            for(int i =0; i<2; i++ ){
              send(sockets[i], &gameover, sizeof(gameover),0);
            }
        }
            //non gagnant
            turn = -turn;
            turnSock = (turnSock + 1) % 2; 
            valid = 0;


    }
    printf("game over \n");
    close(sock1);
    close(sock2);
}


// initialiser le code 
void initMatrix(matrixJType matrixJ[][8]) {

    int blit = -1; 

    // Initialiser la matrix avec 0
    for (int i = 0; i < nbrSquareMat; i++){
        for(int j = 0; j < nbrSquareMat; j++){
            matrixJ[i][j].state = VIDE;
            matrixJ[i][j].couleur = UNDEFINED;
        }
    }
    
    // les premier 2 ligne de la matrixJ doivent etre plein de blanc(-1) 
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < nbrSquareMat; j++){

            if (blit == 1) {
                matrixJ[i][j].couleur = blanc;
                matrixJ[i][j].state = PLEIN;
            }

            blit = -blit;
            
        }
        blit = -blit;
    }

    // les dernier 2 ligne de la matrixJ doivent etre plein de vert (1) 
    blit = 1;
    for (int i = 5; i < nbrSquareMat; i++){
        for (int j = 0; j < nbrSquareMat; j++){

            if (blit == 1){
                matrixJ[i][j].couleur = vert;
                matrixJ[i][j].state = PLEIN;
            }

            blit = -blit;

        }
        blit = -blit;
    }

}



// méthode de logique


int validDePiece(int turn, matrixJType matrixJ[][8], Positions DPositions) {


    if ((matrixJ[DPositions.x][DPositions.y].state == PLEIN) && (matrixJ[DPositions.x][DPositions.y].couleur == turn )){
        return 1; 
    }
    return 0;
 
}

int validAPiece(int turn, matrixJType matrixJ[][8], Positions DE, Positions dest) {

    //blanc bouge a droit
    if ((turn == blanc ) && (matrixJ[dest.x][dest.y].state == VIDE) && (dest.x == DE.x + 1) && (dest.y == DE.y + 1))
        return 1;
    

    // blanc bouge a droit a gauche
    else if ((turn == blanc) && (matrixJ[dest.x][dest.y].state == VIDE) && (dest.x == DE.x + 1) && (dest.y == DE.y-1))
        return 1;

    
     //vert bouge a droit
    else if ((turn == vert) && (matrixJ[dest.x][dest.y].state == VIDE) && (dest.x == DE.x - 1) && (dest.y == DE.y + 1))
        return 1; 

    // vert bouge a droit a gauche
    else if ((turn == vert) && (matrixJ[dest.x][dest.y].state == VIDE) && (dest.x == DE.x - 1)&& (dest.y == DE.y - 1))
        return 1; 

    


    return 0; 
}

int prendPiece(int turn, matrixJType matrixJ[][8], Positions DE, Positions A) {

    // blanc  prend vert a gauche 
    if ((turn == blanc)&& (matrixJ[A.x][A.y].state == VIDE) && (matrixJ[DE.x+1][DE.y-1].couleur == vert)
        && (A.x == DE.x + 2) && (A.y == DE.y -2))

            return blanc_gauche;


    // blanc prend vert a droite 
    else if ((turn == blanc) && (matrixJ[A.x][A.y].state == VIDE) && (matrixJ[DE.x+1][DE.y +1].couleur == vert)
        && (A.x == DE.x + 2) && (A.y == DE.y + 2))

            return blanc_droite;


    // vert prend  blanc piece a gauche
    else if ((turn == vert) &&(matrixJ[A.x][A.y].state == VIDE) && (matrixJ[DE.x-1][DE.y-1].couleur == blanc)
        && (A.x == DE.x -2) && (A.y == DE.y - 2))

            return vert_gauche;     

        

    // vert  prend blanc a droite
    else if ((turn == vert) && (matrixJ[A.x][A.y].state == VIDE) && (matrixJ[DE.x -1][DE.y+1].couleur == blanc)
        && (A.x == DE.x - 2) && (A.y == DE.y + 2)) 

            return vert_droite;


    
}

int gagner(matrixJType matrixJ[][8]) {

    int vertPieces, blancPieces = 0; 
    for(int i = 0; i < nbrSquareMat; i++) {
        for(int j = 0; j < nbrSquareMat; j++) {

            if (matrixJ[i][j].couleur == vert)
                vertPieces++;

            else if (matrixJ[i][j].couleur == blanc) 
                blancPieces++;  
        }
    }

    if (vertPieces == 0 || blancPieces == 0)
        return 1; 
        
    return 0;
}