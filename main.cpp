#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"
#include "winScreen.h"


int main ( int argc, char** argv )
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    atexit(SDL_Quit);
    SDL_Surface *screen = NULL;
    screen = SDL_SetVideoMode(960, 704, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Jeu de dame", NULL);

    TTF_Init();

    menu(screen);

    SDL_FreeSurface(screen);

    SDL_Quit();
    return EXIT_SUCCESS;

}
