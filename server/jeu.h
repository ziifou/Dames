#ifndef JEU
#define JEU 

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>

    #include "constants.h"

    void initGame(SDL_Surface *screen);
    Positions getClick(SDL_Surface *screen);
    void initMatrix(matrixJType matrixJ[][8]);
   
    int validDePiece(int turn, matrixJType matrixJ[][8], Positions DPositions); 
   

   int validAPiece(int turn, matrixJType matrixJ[][8], Positions from, Positions dest);

  
    void refreshMatrix(int turn, matrixJType matrixJ[][8], Positions from, Positions dest);


    int prendPiece(int turn, matrixJType matrixJ[][8], Positions from, Positions dest);

     
    int gagner(matrixJType matrixJ[][8]);


#endif