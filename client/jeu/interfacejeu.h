#ifndef INTERFACEJEU 
#define INTERFACEJEU 

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>

    #include "constants.h"

    
    void printMatrix(SDL_Surface *screen, matrixJType matrixJ[][8], int myturn);

   
    void initMatrix(matrixJType matrixJ[][8]);
    
#endif