#ifndef JEU
#define JEU 

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>

    #include "constants.h"
    #include "interfacejeu.h"
    #include "../network.h"

    void initGame(SDL_Surface *screen, int socket);
    Positions getClick(SDL_Surface *screen);

#endif