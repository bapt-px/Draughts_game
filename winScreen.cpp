#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <math.h>
#include "tools.h"
#include "winScreen.h"
#include "menu.h"
#define nbParticle 1000

void winScreen(SDL_Surface *screen, char winner[20])
{
    bool continuer=true, exit = false;
    SDL_Surface *imageFond, *particle[1024];
    SDL_Event event;
    SDL_Rect position[nbParticle];
    float x[nbParticle], y[nbParticle], timeAlive[nbParticle]={0}, actuelTime[nbParticle]={0}, posX[nbParticle]= {0}, posY[nbParticle]= {0}, oldTime=SDL_GetTicks(), deltaTime;
    int i, time=0;
    char text[1024];
    imageFond = IMG_Load("wallpaper.png");

    for(i=0;i<nbParticle;i++)
    {
        particle[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 2, 2, 32, 0, 0, 0, 0);
        SDL_FillRect(particle[i], NULL, SDL_MapRGB(screen->format, 255, 255, 255));
        posX[i]=screen->w/2;
        posY[i]=screen->h/2;
        timeAlive[i]= rand()%5000;
        x[i] = rand()%10000;
        x[i]/=1000;
        if(rand()%2==0)
            x[i]*=-1;
        if(rand()%2==0)
            y[i]=sqrt(10*10 - (x[i]) * (x[i]) );
        else
            y[i]=-sqrt(10*10 - (x[i]) * (x[i]) );

    }

    while(continuer)
    {
        deltaTime=SDL_GetTicks()- oldTime;
        oldTime=SDL_GetTicks();
        time+=deltaTime;
        for(i=0;i<nbParticle;i++)
            actuelTime[i]+=deltaTime;
        while(time > 1000/60)
        {
            time=0;
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 60, 60, 60));
            SDL_BlitSurface(imageFond, NULL, screen, NULL);
            sprintf(text, "%s a gagne", winner);
            printText(screen, text, 250, 64, "AlphaWood", 75, {255,255,255} );
            for(i=0;i<nbParticle;i++)
            {
                if(actuelTime[i]>timeAlive[i])
                {
                   posX[i]=screen->w/2;
                   posY[i]=screen->h/2;
                   actuelTime[i]=0;
                }
                SDL_BlitSurface(particle[i], NULL, screen, &position[i]);
                posX[i]+=x[i];
                posY[i]+=y[i];
                position[i].x= posX[i];
                position[i].y= posY[i];


            }
            SDL_Flip(screen);
        }
        while(SDL_PollEvent(&event) )
        {
            if(event.type == SDL_QUIT)
            {
                continuer=false;
                exit=true;
            }
            if(event.key.keysym.sym == SDLK_F4)
            {
                continuer=false;
                exit=true;
            }
            if(event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_RETURN || event.type == SDL_MOUSEBUTTONUP)
            {
                continuer=false;
            }
        }
    }
    for(i=0; i<nbParticle; i++)
        SDL_FreeSurface(particle[i]);
    SDL_FreeSurface(imageFond);
    if(!exit)
    menu(screen);
}
