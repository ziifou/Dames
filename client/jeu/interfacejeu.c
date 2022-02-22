#include "interfacejeu.h"
#include <unistd.h>

void printMatrix(SDL_Surface *screen, matrixJType matrixJ[][8], int myturn) {

    SDL_Surface *square[8] = {NULL}, *blancElipse = NULL, *vertElipse = NULL, *myturnLogo = NULL, *blancImg;
    SDL_Rect position; // la position par rapport avec le screen (x,y)
    int squareColor = 1;   
    

    for (int i = 0 ; i < 8; i++)
        square[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,100, 100, 32, 0, 0, 0, 0);

    position.x = 0; 
    position.y = 0; 

    for (int i = 0; i < SQUARE_NUMBERS; i++) {
        for (int j = 0; j < SQUARE_NUMBERS; j++) {

            position.x = j * 100;

            if (squareColor == vert) {
                SDL_FillRect(square[i], NULL, SDL_MapRGB(square[i]->format,238, 58, 130)); // carré rose
            }

            else {
                SDL_FillRect(square[i], NULL, SDL_MapRGB(square[i]->format,0, 0, 0)); // carré noir
            }

            SDL_BlitSurface(square[i], NULL, screen, &position);
            squareColor = -squareColor;
        }
        squareColor = -squareColor;
        position.y = position.y + 100;


    }
    
    blancElipse = IMG_Load("./jeu/Sprites/blanc_elipse.png");
    vertElipse = IMG_Load("./jeu/Sprites/vert_elipse.png");
    blancImg = IMG_Load("./jeu/Sprites/blanc.png");
    
    position.x = 800; 
    position.y = 400;
    SDL_BlitSurface(blancImg , NULL, screen, &position);
    if(myturn == 1){
        
      myturnLogo = IMG_Load("./jeu/Sprites/turn.png");
      
      SDL_BlitSurface(myturnLogo, NULL, screen, &position);
      
    }else if(myturn == 2){
        // le cas de gain
        position.x = 0; 
        position.y = 0;
         myturnLogo = IMG_Load("./jeu/Sprites/felicitation.png");
      
        SDL_BlitSurface(myturnLogo, NULL, screen, &position);
        SDL_Flip(screen);
          return;
    }else if(myturn == 3){
        // le cas de perte
        position.x = 0; 
        position.y = 0;
        myturnLogo = IMG_Load("./jeu/Sprites/perdant.png");
        SDL_BlitSurface(myturnLogo, NULL, screen, &position);
        SDL_Flip(screen);
        return;
    }
    else {
      myturnLogo = IMG_Load("./jeu/Sprites/notturn.png");
      
      SDL_BlitSurface(myturnLogo, NULL, screen, &position);
      
    }

    
    for(int i = 0; i < SQUARE_NUMBERS; i++){
        for(int j = 0; j < SQUARE_NUMBERS; j++){
            position.x = j * 100; 
            position.y = i * 100;

            if (matrixJ[i][j].state == PLEIN && matrixJ[i][j].couleur == blanc) {
                SDL_BlitSurface(blancElipse, NULL, screen, &position);

            }

            else if (matrixJ[i][j].state == PLEIN && matrixJ[i][j].couleur == vert){

                SDL_BlitSurface(vertElipse, NULL, screen, &position);
            }
        }
    }

    

    SDL_Flip(screen);
}

void initMatrix(matrixJType matrixJ[][8]) {

    int blit = -1; 

     
    for (int i = 0; i < SQUARE_NUMBERS; i++){
        for(int j = 0; j < SQUARE_NUMBERS; j++){
            matrixJ[i][j].state = VIDE;
            matrixJ[i][j].couleur = UNDEFINED;
        }
    }
    
   
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < SQUARE_NUMBERS; j++){

            if (blit == 1) {
                matrixJ[i][j].couleur = blanc;
                matrixJ[i][j].state = PLEIN;
            }

            blit = -blit;
            
        }
        blit = -blit;
    }

   

    blit = 1;
    for (int i = 5; i < SQUARE_NUMBERS; i++){
        for (int j = 0; j < SQUARE_NUMBERS; j++){

            if (blit == 1){
                matrixJ[i][j].couleur = vert;
                matrixJ[i][j].state = PLEIN;
            }

            blit = -blit;

        }
        blit = -blit;
    }

}
