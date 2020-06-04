#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include "tools.h"

void printText(SDL_Surface *screen, char text[], int x, int y, char police[], int sz, SDL_Color color)
{
    SDL_Surface *surface;
    SDL_Rect position;
    TTF_Font *font = NULL;
    char fontText[100];

    position.x = x;
    position.y = y;

    sprintf(fontText,"%s.ttf", police);
    font = TTF_OpenFont(fontText, sz);

    surface = TTF_RenderText_Blended(font, text, color);
    SDL_BlitSurface(surface, NULL, screen, &position);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

bool whereMoveDame(int plateau[10][10], int tableau[2], int tableau2[20][2], int tour, int pionManger[20][2])
{
    int x1, x2, x3, x4, y1, y2, y3, y4, index=0, i;
    bool canEat=false, bd=true, bg=true, hg=true, hd=true;

    x1=tableau[1];   x2=tableau[1];  x3=tableau[1];  x4=tableau[1];
    y1=tableau[0]; y2=tableau[0]; y3=tableau[0]; y4=tableau[0];
    while(bd||bg||hg||hd)
    {
        bd=false, bg=false, hg=false, hd=false;
        if(x1==0)
        {  x1=9;     x3=8;   }
        else
       {
            x1--;
          if(x1==0)
            x3=9;
          else
            x3 = x1-1;
       }
        if(x2==9)
        { x2=0; x4=1;  }
        else
        {
          x2++;
          if(x2==9)
            x4=0;
          else
            x4 = x2+1;
        }
        if(tour==1)
        {
            y1++;
            y2 = y1+1;
            y3--;
            y4 = y3-1;
        }
        else
        {
            y1--;
            y2 = y1-1;
            y3++;
            y4 = y3+1;
        }

        if((plateau[y2][x3] == 0 && (plateau[y1][x1] == 2 || plateau[y1][x1] == 4) && tour==1) ||
           (plateau[y2][x3] == 0 && (plateau[y1][x1] == 1 || plateau[y1][x1] == 3) && tour==2) )
        {
            tableau2[index][0]=y2;
            tableau2[index][1]=x3;
            pionManger[index][0]=y1;
            pionManger[index][1]=x1;
            index++;
            canEat=true;
            hg=true;
        }
        if ( (plateau[y4][x3] == 0 && (plateau[y3][x1] == 2 || plateau[y3][x1] == 4) && tour==1) ||
           (plateau[y4][x3] == 0 && (plateau[y3][x1] == 1 || plateau[y3][x1] == 3) && tour==2) )
        {
            tableau2[index][0]=y4;
            tableau2[index][1]=x3;
            pionManger[index][0]=y3;
            pionManger[index][1]=x1;
            index++;
            canEat=true;
            bg=true;
        }

        if((plateau[y2][x4] == 0 && (plateau[y1][x2] == 2 || plateau[y1][x2] == 4) && tour == 1) ||
           (plateau[y2][x4] == 0 && (plateau[y1][x2] == 1 || plateau[y1][x2] == 3) && tour == 2) ||
           (plateau[y4][x4] == 0 && (plateau[y3][x2] == 2 || plateau[y3][x2] == 4) && tour == 1) ||
           (plateau[y4][x4] == 0 && (plateau[y3][x2] == 1 || plateau[y3][x2] == 3) && tour == 2) )
        {
            tableau2[index][0]=y2;
            tableau2[index][1]=x4;
            pionManger[index][0]=y1;
            pionManger[index][1]=x2;
            index++;
            canEat=true;
            hd=true;
        }
        if ( (plateau[y4][x4] == 0 && plateau[y3][x2] == 2 && tour == 1) ||
           (plateau[y4][x4] == 0 && plateau[y3][x2] == 1 && tour == 2) )
           {
            tableau2[index][0]=y4;
            tableau2[index][1]=x4;
            pionManger[index][0]=y3;
            pionManger[index][1]=x2;
            index++;
            canEat=true;
            bd=true;
            }
        if(plateau[y1][x1] == 0 && !canEat)
        {
            tableau2[index][0]=y1;
            tableau2[index][1]=x1;
            index++;
            hg=true;
        }
        if(plateau[y3][x1] == 0 && !canEat)
        {
            tableau2[index][0]=y3;
            tableau2[index][1]=x1;
            index++;
            bg=true;
        }
        if(plateau[y3][x2] == 0 && !canEat)
        {
            tableau2[index][0]=y3;
            tableau2[index][1]=x2;
            index++;
            bd=true;
        }
        if(plateau[y1][x2] == 0 && !canEat)
        {
            tableau2[index][0]=y1;
            tableau2[index][1]=x2;
            index++;
            hd=true;
        }
        if(!bg&&!bd&&!hg&&!hd)
        {
            tableau2[index][0]=-1;
        }
    }
    return canEat;
}
