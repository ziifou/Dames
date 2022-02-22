#include "jeu.h" 

void initGame(SDL_Surface *screen, int socket) {
    matrixJType matrixJ[8][8]; 
    Positions APositions; // a la position
    Positions DPositions; // de la position
    Positions click; 
    int gameover = 0;
    int turn = vert;
    int valid= 0;
    int myturn =0;
    recv(socket, &turn, sizeof(turn), 0);
    initMatrix(matrixJ); 
    
    while (!gameover) {

        if((recv(socket, &myturn, sizeof(myturn), 0)) <= 0) exit(EXIT_FAILURE);
        printMatrix(screen, matrixJ, myturn);

        if(myturn){
          
            while(valid != 2){
              click = getClick(screen);
              printf("je clique moi \n");
              send(socket, &click, sizeof(click), 0);
              //recv la reponse du serveur
              if((recv(socket, &valid, sizeof(valid), 0))<= 0) exit(EXIT_FAILURE);
              }
        }
        //mise a jour de jeu
        if((recv(socket, &turn, sizeof(int), 0)) <= 0) exit(EXIT_FAILURE);
        if((recv(socket, &matrixJ, sizeof(matrixJ ), 0))<= 0) exit(EXIT_FAILURE);
        if((recv(socket, &DPositions, sizeof(DPositions), 0))<= 0) exit(EXIT_FAILURE);
        if((recv(socket, &APositions, sizeof(APositions), 0))<= 0) exit(EXIT_FAILURE);
       
        // y a t il un gagnant ???
        
        if((recv(socket, &gameover, sizeof(gameover),0))<= 0) 
           exit(EXIT_FAILURE);
      
        valid = 0;
        printf("\n\n\n");
        
        
    }
    printMatrix(screen, matrixJ, gameover);
    sleep(10);
    
    exit(0);


}


Positions getClick(SDL_Surface *screen){

    Positions mousePosition; 
    SDL_Event event;
    int wait = 1;

    while (wait)
    {

        SDL_Flip(screen);
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                exit(0);

            case SDL_MOUSEBUTTONDOWN:
                mousePosition.x = event.button.y;
                mousePosition.y = event.button.x;


                if ((mousePosition.x / 100 < 8) && (mousePosition.y / 100 < 8))
                 {
                     mousePosition.x = mousePosition.x / 100;  
                     mousePosition.y = mousePosition.y / 100;
                     return mousePosition;

                 }

                break;
        }
    }
}
