#include "main.h"


void lunchGame(int socket) {

  SDL_Surface *screen = NULL;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Dames ", NULL);

  screen = SDL_SetVideoMode(1000, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

  if (screen == NULL) {
    exit(EXIT_FAILURE);
  }


  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
  initGame(screen, socket);
  SDL_Quit();
  
}
