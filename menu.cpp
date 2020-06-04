
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "menu.h"
#include "tools.h"
#include "jeu.h"


void menu(SDL_Surface* screen)
{
    int index=0, etape=0;
    bool continuer=true, exit =false;
    SDL_Surface *imageMenu;
    SDL_Event event;
    char text[20]={0}, text2[20]={0};
    imageMenu = IMG_Load("wallpaper.png");
    while(continuer)
    {
      if(etape==3)
            continuer=false;
        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_QUIT)
            {
                continuer=false;
                exit=true;
            }
            if(event.type == SDL_MOUSEBUTTONUP && etape==0)
            {
                if(event.button.x<500)
                {   etape=3; sprintf(text,"Ordinateur"); sprintf(text2, "joueur");}
                else
                {  etape++;  }
            }
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_F4)
                {
                    continuer=false;
                    exit=true;
                }
                if((event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_KP1 ) && etape ==0)
                {  etape=3;  sprintf(text,"Ordinateur"); sprintf(text2, "joueur"); }
                if((event.key.keysym.sym == SDLK_2 || event.key.keysym.sym == SDLK_KP2 ) && etape ==0)
                    etape++;

                if(etape == 1 || etape == 2)
                {
                    if(index<16 && event.key.keysym.sym >=97 && event.key.keysym.sym <= 122)
                    {
                        if(etape==1)
                            text[index] = event.key.keysym.sym;
                        else
                            text2[index] = event.key.keysym.sym;
                        index++;
                    }
                    else if(event.key.keysym.sym==SDLK_BACKSPACE)
                    {
                        if(etape==1)
                            text[index]=32;
                        else
                            text2[index]=32;
                        if(index!=0)
                            index--;
                    }
                    else if(event.key.keysym.sym==SDLK_RETURN)
                    { index=0;    etape++;    }

                }
            }
            SDL_BlitSurface(imageMenu, NULL, screen, NULL);
            if(etape == 0)
            {
                printText(screen, "Jeu de dame", 200, 5, "AlphaWood", 100, {255,255,255});
                printText(screen, "1. Jouer contre IA", 32, 165, "angelina", 50, {255,255,255});
                printText(screen, "2. Jouer contre un joueur", 480, 165, "angelina", 50, {255,255,255});
            }
            if(etape == 1 || etape == 2)
            {
                SDL_BlitSurface(imageMenu, NULL, screen, NULL);
                printText(screen, "Jeu de dame", 200, 5, "AlphaWood", 100, {255,255,255});
                if(etape==1)
                {
                    printText(screen, "Choisir pseudo joueur 1 :", 32, 165, "angelina", 50, {255,255,255});
                    printText(screen, text  , 460, 165, "angelina", 50, {255,255,255});
                }
                else
                {
                    printText(screen, "Choisir pseudo joueur 2 :", 32, 165, "angelina", 50, {255,255,255});
                    printText(screen, text2, 460, 165, "angelina", 50, {255,255,255});
                }
            }
            SDL_Flip(screen);
        }
    }
    SDL_FreeSurface(imageMenu);
    if(!exit)
        jeu(screen, text, text2);
}
