#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>
#include "tools.h"
#include "menu.h"
#include "winScreen.h"
#define SIZE 10

void possibility(int plateau[SIZE][SIZE], int tableau[20][2], int tour)
{
    int i, j, index=0, x1, x2, x3, x4, y1, y2, y3, y4;
    bool canEat=false, isDame[20]={false};
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
        {
            if(plateau[i][j]==tour)
            {
                  tableau[index][0]=i;
                  tableau[index][1]=j;
                  index++;
            }
            else if(plateau[i][j]==tour+2)
            {
                  isDame[index]=true;
                  tableau[index][0]=i;
                  tableau[index][1]=j;
                  index++;
            }
        }
    }
        for(i=0; i<index; i++)
        {

                if(tableau[i][1]==0)
                {  x1=9; x3=8;    }
                else
                {  x1 = tableau[i][1]-1;   x3 = x1-1;   }
                if(tableau[i][1]==9)
                { x2=0;   x4=1; }
                else
                { x2 = tableau[i][1]+1;   x4 = x2+1;   }
                if(tableau[i][1]==1)
                    x3=9;
                if(tableau[i][1]==8)
                    x4=0;
                if(tour==1)
                {
                    y1 = tableau[i][0] + 1 ;
                    y2 = tableau[i][0] + 2 ;
                    y3 = tableau[i][0] - 1 ;
                    y4 = tableau[i][0] - 2 ;
                }
                else
                {
                    y1 = tableau[i][0] - 1 ;
                    y2 = tableau[i][0] - 2 ;
                    y3 = tableau[i][0] + 1 ;
                    y4 = tableau[i][0] + 2 ;
                }

                if(((
                        ( (plateau[y2][x3] == 0 || plateau[y2][tableau[i][1]] == 0  || plateau[tableau[i][0]][x3] ==0) && (plateau[y1][x1] == 2 || plateau[y1][x1] == 4) )  ||
                        ( (plateau[y2][x4] == 0 || plateau[y2][tableau[i][1]] == 0  || plateau[tableau[i][0]][x4] ==0) && (plateau[y1][x2] == 2 || plateau[y1][x2] == 4) )  ||
                        ( (plateau[y4][x3] == 0 || plateau[y4][tableau[i][1]] == 0  || plateau[tableau[i][0]][x3] ==0) && (plateau[y3][x1] == 2 || plateau[y3][x1] == 4) )  ||
                        ( (plateau[y4][x4] == 0 || plateau[y4][tableau[i][1]] == 0  || plateau[tableau[i][0]][x4] ==0) && (plateau[y3][x2] == 2 || plateau[y3][x2] == 4) )
                       ) && tour == 1) ||
                       ((
                         ( (plateau[y2][x3] == 0 || plateau[y2][tableau[i][1]] == 0  || plateau[tableau[i][0]][x3] ==0) && (plateau[y1][x1] == 1 || plateau[y1][x1] == 3))  ||
                         ( (plateau[y2][x4] == 0 || plateau[y2][tableau[i][1]] == 0  || plateau[tableau[i][0]][x4] ==0) && (plateau[y1][x2] == 1 || plateau[y1][x2] == 3))  ||
                         ( (plateau[y4][x3] == 0 || plateau[y4][tableau[i][1]] == 0  || plateau[tableau[i][0]][x3] ==0) && (plateau[y3][x1] == 1 || plateau[y3][x1] == 3))  ||
                         ( (plateau[y4][x4] == 0 || plateau[y4][tableau[i][1]] == 0  || plateau[tableau[i][0]][x4] ==0)&&  (plateau[y3][x2] == 1 || plateau[y3][x2] == 3))
                        ) && tour == 2)
                  )
                {
                    if(!canEat)
                    {
                        for(j=0; j<i; j++)
                            tableau[j][0]=-1;
                        canEat=true;
                    }

                }

                else if((plateau[y1][x1] == 0 || plateau[y1][x2] == 0 || (isDame[i] && (plateau[y3][x1] == 0 || plateau[y3][x2] == 0 )) ) && !canEat    )
                {
                    if(isDame[i])
                        if(whereMoveDame(plateau, tableau[i], new int[20][2], tour, new int[20][2]) )
                           {
                               if(!canEat)
                                {
                                    for(j=0; j<i; j++)
                                        tableau[j][0]=-1;
                                    canEat=true;
                                }
                           }
                }
                else
                 tableau[i][0]=-1;
//            else
//                possibilityDame(platea)
        }
}
bool whereMove(int plateau[10][10], int tableau[2], int tableau2[20][2], int tour, int pionManger[20][2])
{
    int x1, x2, x3, x4, y1, y2, y3, y4, index=0, i;
    bool canEat=false, canMove=false;
    for(i=0;i<20; i++)
        tableau2[i][0]=-1;
    if(plateau[tableau[0]][tableau[1]] > 2)
        return whereMoveDame(plateau, tableau, tableau2, tour, pionManger);
    x1=tableau[1];   x2=tableau[1];  x3=tableau[1];  x4=tableau[1];
    y1=tableau[0]; y2=tableau[0]; y3=tableau[0]; y4=tableau[0];
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
            canMove=true;
        }
        if((plateau[y2][tableau[1]] == 0 && (plateau[y1][x1] == 2 || plateau[y1][x1] == 4) && tour==1) ||
           (plateau[y2][tableau[1]] == 0 && (plateau[y1][x1] == 1 || plateau[y1][x1] == 3) && tour==2) )
        {
            tableau2[index][0]=y2;
            tableau2[index][1]=tableau[1];
            pionManger[index][0]=y1;
            pionManger[index][1]=x1;
            index++;
            canEat=true;
            canMove=true;
        }
        if((plateau[tableau[0]][x3] == 0 && (plateau[y1][x1] == 2 || plateau[y1][x1] == 4) && tour==1) ||
           (plateau[tableau[0]][x3] == 0 && (plateau[y1][x1] == 1 || plateau[y1][x1] == 3) && tour==2) )
        {
            tableau2[index][0]=tableau[0];
            tableau2[index][1]=x3;
            pionManger[index][0]=y1;
            pionManger[index][1]=x1;
            index++;
            canEat=true;
            canMove=true;
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
            canMove=true;
        }
        if ( ( plateau[y4][tableau[1]] == 0 && (plateau[y3][x1] == 2 || plateau[y3][x1] == 4) && tour==1) ||
             ( plateau[y4][tableau[1]] == 0 && (plateau[y3][x1] == 1 || plateau[y3][x1] == 3) && tour==2) )
        {
            tableau2[index][0]=y4;
            tableau2[index][1]=tableau[1];
            pionManger[index][0]=y3;
            pionManger[index][1]=x1;
            index++;
            canEat=true;
            canMove=true;
        }
        if ( (plateau[tableau[0]][x3] == 0 && (plateau[y3][x1] == 2 || plateau[y3][x1] == 4) && tour==1) ||
             (plateau[tableau[0]][x3] == 0 && (plateau[y3][x1] == 1 || plateau[y3][x1] == 3) && tour==2) )
        {
            tableau2[index][0]=tableau[0];
            tableau2[index][1]=x3;
            pionManger[index][0]=y3;
            pionManger[index][1]=x1;
            index++;
            canEat=true;
            canMove=true;
        }

        if((plateau[y2][x4] == 0 && (plateau[y1][x2] == 2 || plateau[y1][x2] == 4) && tour == 1) ||
           (plateau[y2][x4] == 0 && (plateau[y1][x2] == 1 || plateau[y1][x2] == 3) && tour == 2) )

        {
            tableau2[index][0]=y2;
            tableau2[index][1]=x4;
            pionManger[index][0]=y1;
            pionManger[index][1]=x2;
            index++;
            canEat=true;
            canMove=true;
        }

        if(( plateau[y2][tableau[1]] == 0 && (plateau[y1][x2] == 2 || plateau[y1][x2] == 4) && tour == 1) ||
           ( plateau[y2][tableau[1]] == 0 && (plateau[y1][x2] == 1 || plateau[y1][x2] == 3) && tour == 2) )

        {
            tableau2[index][0]=y2;
            tableau2[index][1]=tableau[1];
            pionManger[index][0]=y1;
            pionManger[index][1]=x2;
            index++;
            canEat=true;
            canMove=true;
        }
        if(( plateau[tableau[0]][x4] ==0  && (plateau[y1][x2] == 2 || plateau[y1][x2] == 4) && tour == 1) ||
           ( plateau[tableau[0]][x4] ==0  && (plateau[y1][x2] == 1 || plateau[y1][x2] == 3) && tour == 2) )

        {
            tableau2[index][0]=tableau[0];
            tableau2[index][1]=x4;
            pionManger[index][0]=y1;
            pionManger[index][1]=x2;
            index++;
            canEat=true;
            canMove=true;
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
                canMove=true;
            }
        if((plateau[tableau[0]][x4] == 0 && (plateau[y3][x2] == 2 || plateau[y3][x2] == 4) && tour == 1) ||
           (plateau[tableau[0]][x4] == 0 && (plateau[y3][x2] == 1 || plateau[y3][x2] == 3) && tour == 2) )
           {
                tableau2[index][0]=tableau[0];
                tableau2[index][1]=x4;
                pionManger[index][0]=y3;
                pionManger[index][1]=x2;
                index++;
                canEat=true;
                canMove=true;
           }
        if ( (plateau[y4][tableau[1]] == 0 && plateau[y3][x2] == 2 && tour == 1) ||
           (plateau[y4][tableau[1]] == 0 && plateau[y3][x2] == 1 && tour == 2) )
           {
            tableau2[index][0]=y4;
            tableau2[index][1]=tableau[1];
            pionManger[index][0]=y3;
            pionManger[index][1]=x2;
            index++;
            canEat=true;
            canMove=true;
            }


        if(plateau[y1][x1] == 0 && !canEat)
        {
            tableau2[index][0]=y1;
            tableau2[index][1]=x1;
            index++;
            canMove=true;
        }
        if(plateau[y1][x2] == 0 && !canEat)
        {
            tableau2[index][0]=y1;
            tableau2[index][1]=x2;
            index++;
            canMove=true;
        }
        if(!canMove)
        {
            tableau2[index][0]=-1;
        }
    return canEat;
}
int tryKey(int tableau[20][2], int key)
{
    bool containKeys=false;
    int i, j, index=0;
    if(key >=97 && key < 107 && !containKeys)
    {
        for(i=0; i<20; i++)
        {
            if(tableau[i][0]!=-1)
            {
                if( tableau[i][1] == key - 97)
                {
                    index++;
                    if(!containKeys)
                    {
                        containKeys=true;
                        for(j=0;j<i;j++)
                            tableau[j][0]=-1;
                    }
                }
                else if(containKeys)
                    tableau[i][0]=-1;
            }
        }
    }
    else if(key >=48 && key < 58 && !containKeys)
    {
        for(i=0; i<20; i++)
        {
            if(tableau[i][0]!=-1)
            {
                if( tableau[i][0] == key - 48)
                {
                    index++;
                    if(!containKeys)
                    {
                        containKeys=true;
                        for(j=0;j<i;j++)
                            tableau[j][0]=-1;
                    }
                }
                else if(containKeys)
                    tableau[i][0]=-1;
            }
        }
    }
    i=0;
    if(index==1)
   {
        while(tableau[i][0]==-1)
            i++;
        tableau[0][0]=tableau[i][0];
        tableau[0][1]=tableau[i][1];
        return i;               // renvoie l'index selectionner
   }
    return -1;

}
void jeu(SDL_Surface *screen, char joueur1[20], char joueur2[])
{
    int plateau[SIZE][SIZE], i, j, r, index=0, pionMove[20][2]={0}, posMove[20][2]={0}, tour=1, pionManger[20][2], capturer[2][20]={0}, index2=0, index3=0, k=0, z, moveMouse[20], choiseMouse=0, timePlay=0;
    bool continuer=true, containLetter=false, containNumber=false, canEat, isTest=false, step1=false, step2=false, exit=false, vsIA;
    char letter[10], text3[1024], copie[20] = {0};
    float deltaTime, oldTime=SDL_GetTicks(), timeAnimation=700, time;
    SDL_Surface *s1 = NULL, *s2, *pion1, *pion2, *dame1, *dame2, *pionPossible, *explosion[23];
    SDL_Event event;
    SDL_Rect position;
    sprintf(copie, "Ordinateur");
    vsIA=true;
    for(i=0;i<10;i++)
        if(copie[i]!=joueur1[i])
            vsIA=false;
    s1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 64, 64, 32, 0, 0, 0, 0);
    SDL_FillRect(s1, NULL, SDL_MapRGB(screen->format, 189, 149, 92));
    s2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 64, 64, 32, 0, 0, 0, 0);
    SDL_FillRect(s2, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    pionPossible = SDL_CreateRGBSurface(SDL_HWSURFACE, 64, 64, 32, 0, 0, 0, 0);
    SDL_FillRect(pionPossible, NULL, SDL_MapRGB(screen->format, 181, 69, 64));
    for(i=1;i<=23;i++)
    {
        explosion[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 64, 64, 32, 0, 0, 0, 0);
        SDL_FillRect(explosion[i], NULL, SDL_MapRGB(screen->format, 255, 255, 255));
        sprintf(text3, "animation/%d.png",i);
        explosion[i-1] = IMG_Load(text3);
            SDL_SetColorKey(explosion[i-1], SDL_SRCCOLORKEY, SDL_MapRGB(explosion[i-1]->format, 255, 255, 255));
    }
    SDL_SetAlpha(pionPossible,SDL_SRCALPHA, 170);
    pion1 = SDL_LoadBMP("pion1.bmp");
    pion2 = SDL_LoadBMP("pion2.bmp");
    dame1 = IMG_Load("dame1.png");
    dame2 = SDL_LoadBMP("dame2.bmp");
    SDL_SetColorKey(pion1, SDL_SRCCOLORKEY, SDL_MapRGB(pion1->format, 255, 255, 255));
    SDL_SetColorKey(pion2, SDL_SRCCOLORKEY, SDL_MapRGB(pion2->format, 255, 255, 255));
    SDL_SetColorKey(dame2, SDL_SRCCOLORKEY, SDL_MapRGB(dame2->format, 255, 255, 255));

    for(i=0; i<SIZE; i++)
        for(j=0; j<SIZE; j++)
        {
            if((i+j)%2 == 1 && i<4)
                plateau[i][j]=1;
            else if((i+j)%2 == 1 && i>5)
                plateau[i][j]=2;
            else
                plateau[i][j]=0;
        }


      for(i=0;i<20; i++)
        posMove[i][0]=-1;

    possibility(plateau, pionMove, tour);
    while(continuer)
    {
        deltaTime = SDL_GetTicks() - oldTime;
        oldTime = SDL_GetTicks();
        timeAnimation+=deltaTime;
        time+=deltaTime;
        timePlay+=deltaTime;

        if(vsIA && tour==1)                     // jeu de l'IA
        {
            if(timePlay>400 && !step1)
            {
                r=rand()%20;
                while(pionMove[r][0]==-1)
                    r=rand()%20;
                pionMove[0][0]=pionMove[r][0];
                pionMove[0][1]=pionMove[r][1];
               for(i=1;i<20;i++)
                    pionMove[i][0]=-1;
               canEat = whereMove(plateau, pionMove[0], posMove, tour, pionManger);
               step1=true;
            }
             else if(timePlay>=800 && step1)
            {
                r=rand()%20;
                while(posMove[r][0]==-1)
                    r=rand()%20;
                z=r;
                posMove[0][0]=posMove[r][0];
                posMove[0][1]=posMove[r][1];
                step1=false;
                if(posMove[0][0] == 9 ||  plateau[ pionMove[0][0] ] [pionMove[0][1] ] == 3 )
                    plateau[ posMove[0][0] ] [posMove[0][1] ] = 3;
                else
                    plateau[ posMove[0][0] ] [posMove[0][1] ] = 1;
                plateau[ pionMove[0][0] ] [pionMove[0][1] ] = 0;
                if(canEat)
                {
                    plateau[ pionManger[k][0]] [pionManger[k][1]] = 0;
                    capturer[0][index2]=plateau[ posMove[0][0] ] [posMove[0][1] ] ;
                    index2++;
                    timeAnimation=0;
                }
                tour=2;
                for(i=0;i<20; i++)
                    pionMove[i][0]=-1;
                    possibility(plateau, pionMove, tour);
                for(i=0;i<20; i++)
                    posMove[i][0]=-1;
                }
        }

        while(SDL_PollEvent(&event) )
        {
            if(event.type == SDL_QUIT)
             {
                continuer=false;
                exit=true;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN && timePlay > 1000)            // jeu joueur selection du pion a la souris
            {
                for(i=0; i<20; i++)
                {
                    if(pionMove[i][0]!=-1)
                        moveMouse[i] = sqrt( ((pionMove[i][1]+1)*64 - event.motion.x) * ((pionMove[i][1]+1)*64 - event.motion.x) + ((pionMove[i][0]+1)*64 - event.motion.y) * ((pionMove[i][0]+1)*64 - event.motion.y)  );
                    else
                        moveMouse[i]=1000;
                    if(moveMouse[i]<moveMouse[choiseMouse])
                        choiseMouse=i;
                }
                  pionMove[0][0]=pionMove[choiseMouse][0];
                  pionMove[0][1]=pionMove[choiseMouse][1];
                  for(i=1;i<20;i++)
                        pionMove[i][0]=-1;
                    z=r;
                    canEat = whereMove(plateau, pionMove[0], posMove, tour, pionManger);
            }
            if(event.type == SDL_MOUSEBUTTONUP && timePlay>1000)            // jeu joueur selection du deplacement a la souris
            {

               for(i=0; i<20; i++)
                {
                     if(posMove[i][0]!=-1)
                        moveMouse[i] = sqrt( ((posMove[i][1]+1)*64 - event.motion.x) * ((posMove[i][1]+1)*64 - event.motion.x) + ((posMove[i][0]+1)*64 - event.motion.y) * ((posMove[i][0]+1)*64 - event.motion.y)  );
                    else
                        moveMouse[i]=1000;
                    if(moveMouse[i]<moveMouse[k])
                        k=i;
                }
                     posMove[0][0]=posMove[k][0];
                     posMove[0][1]=posMove[k][1];
                    for(i=1;i<20;i++)
                        posMove[i][0]=-1;
                    z=k;
                    if(tour==1 )
                    {
                            if(posMove[0][0] == 9 ||  plateau[ pionMove[0][0] ] [pionMove[0][1] ] == 3 )
                                plateau[ posMove[0][0] ] [posMove[0][1] ] = 3;
                            else
                                plateau[ posMove[0][0] ] [posMove[0][1] ] = 1;
                            plateau[ pionMove[0][0] ] [pionMove[0][1] ] = 0;
                            if(canEat)
                            {
                                plateau[ pionManger[k][0]] [pionManger[k][1]] = 0;
                                capturer[0][index2]=plateau[ posMove[0][0] ] [posMove[0][1] ] ;
                                index2++;
                                timeAnimation=0;
                            }
                            tour=2;
                    }
                   else
                    {
                        if( posMove[0][0] == 0 || plateau[ pionMove[0][0] ] [pionMove[0][1] ]== 4)
                            plateau[ posMove[0][0] ] [posMove[0][1] ] = 4;
                        else
                            plateau[ posMove[0][0] ] [posMove[0][1] ] = 2;
                        plateau[ pionMove[0][0] ] [pionMove[0][1] ] = 0;
                        if(canEat)
                        {
                            plateau[ pionManger[k][0]] [pionManger[k][1]] = 0;
                            capturer[1][index3]=plateau[ posMove[0][0] ] [posMove[0][1] ];
                            index3++;
                            timeAnimation=0;
                        }
                        tour=1;
                    }
                for(i=0;i<20; i++)
                    pionMove[i][0]=-1;
                    possibility(plateau, pionMove, tour);
                for(i=0;i<20; i++)
                    posMove[i][0]=-1;
                timePlay=0;
            }
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_F4)
                {
                    continuer=false;
                    exit=true;
                }
                if(event.key.keysym.sym == SDLK_ESCAPE)         // permet de revenir en arriere si le pion est deja selectionner
                {
                    possibility(plateau, pionMove, tour);
                    for(i=0;i<20; i++)
                        posMove[i][0]=-1;
                }
                if(tryKey(pionMove, event.key.keysym.sym)!=-1)      // jeu joueur au clavier
                   canEat = whereMove(plateau, pionMove[0], posMove, tour, pionManger);
                k=tryKey(posMove, event.key.keysym.sym);
                if(k!=-1)
                {
                    z=k;
                    if(tour==1)
                    {
                        if(posMove[0][0] == 9 ||  plateau[ pionMove[0][0] ] [pionMove[0][1] ] == 3 )
                            plateau[ posMove[0][0] ] [posMove[0][1] ] = 3;
                        else
                            plateau[ posMove[0][0] ] [posMove[0][1] ] = 1;
                        plateau[ pionMove[0][0] ] [pionMove[0][1] ] = 0;
                        if(canEat)
                        {
                            plateau[ pionManger[k][0]] [pionManger[k][1]] = 0;
                            capturer[0][index2]=plateau[ posMove[0][0] ] [posMove[0][1] ] ;
                            index2++;
                            timeAnimation=0;
                        }
                        tour=2;
                    }
                   else
                    {
                        if( posMove[0][0] == 0 || plateau[ pionMove[0][0] ] [pionMove[0][1] ]== 4)
                            plateau[ posMove[0][0] ] [posMove[0][1] ] = 4;
                        else
                            plateau[ posMove[0][0] ] [posMove[0][1] ] = 2;
                        plateau[ pionMove[0][0] ] [pionMove[0][1] ] = 0;
                        if(canEat)
                        {
                            plateau[ pionManger[k][0]] [pionManger[k][1]] = 0;
                            capturer[1][index3]=plateau[ posMove[0][0] ] [posMove[0][1] ];
                            index3++;
                            timeAnimation=0;
                        }
                        tour=1;
                    }
                    for(i=0;i<20; i++)
                        pionMove[i][0]=-1;
                    possibility(plateau, pionMove, tour);
                    for(i=0;i<20; i++)
                        posMove[i][0]=-1;

                }
                timePlay=0;
            }
            if(index2==19 || index3==19 )
            {
                continuer=false;
            }
        }

        if(time > 1000/60) // Affichage rafraichi 60x par seconde
        {
            time=0;
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 60, 60, 60));
            for(i=0; i<SIZE; i++)
            {
                sprintf(letter,"%c",i+65);
                printText(screen, letter, i*64 + 64, 6, "arial", 15, {255,255,255});
                sprintf(letter,"%d",i);
                printText(screen, letter, 6, i*64 + 52, "arial", 15, {255,255,255});
            }
            for(i=0; i<SIZE; i++)
                for(j=0; j<SIZE; j++)
                {
                    position.x=j*64 + 32;
                    position.y=i*64 + 32;
                    if((i+j)%2==0)
                        SDL_BlitSurface(s1, NULL, screen, &position);
                    else
                        SDL_BlitSurface(s2, NULL, screen, &position);
                    if(plateau[i][j]==1)
                        SDL_BlitSurface(pion1, NULL, screen, &position);
                    if(plateau[i][j]==2)
                        SDL_BlitSurface(pion2, NULL, screen, &position);
                    if(plateau[i][j]==3)
                        SDL_BlitSurface(dame1, NULL, screen, &position);
                    if(plateau[i][j]==4)
                        SDL_BlitSurface(dame2, NULL, screen, &position);
                }

            printText(screen, joueur1, 700, 6, "angelina", 50, {255,255,255});
            printText(screen, joueur2, 700, 650, "angelina", 50, {255,255,255});

            for(i=0; i<20; i++)
            {
                if(pionMove[i][0]!=-1)
                {
                    position.x = pionMove[i][1]*64 + 32;
                    position.y = pionMove[i][0]*64 + 32;
                    SDL_BlitSurface(pionPossible, NULL, screen, &position);
                }
                if(posMove[i][0] != -1)
                {
                    position.x = posMove[i][1]*64 + 32;
                    position.y = posMove[i][0]*64 + 32;
                    SDL_BlitSurface(pionPossible, NULL, screen, &position);
                }
            }
            for(i=0; i< index2; i++)
            {
                position.x = 900-12*i;
                position.y = 600;
                if(capturer[0][i]==1)
                    SDL_BlitSurface(pion2, NULL, screen, &position);
                else
                    SDL_BlitSurface(dame2, NULL, screen, &position);
                }
            for(i=0; i< index3; i++)
            {
                position.x = 900-12*i;
                position.y = 50;
                if(capturer[1][i]==2)
                    SDL_BlitSurface(pion1, NULL, screen, &position);
                else
                    SDL_BlitSurface(dame1, NULL, screen, &position);
            }
            if(timeAnimation<700)
            {
                position.y = 64*pionManger[z][0] + 96 - explosion[0]->h;
                position.x = 64*pionManger[z][1] + 32;
                SDL_BlitSurface(explosion[(int)timeAnimation / (700/22)], NULL, screen, &position);
            }
            SDL_Flip(screen);
        }
    }

    SDL_FreeSurface(s1);
    SDL_FreeSurface(s2);
    SDL_FreeSurface(dame1);
    SDL_FreeSurface(dame2);
    SDL_FreeSurface(pion1);
    SDL_FreeSurface(pion2);
    SDL_FreeSurface(pionPossible);
    for(i=0;i<23;i++)
        SDL_FreeSurface(explosion[i]);
    if(!exit)
        if(index2 ==19)
            winScreen(screen, joueur1);
        else
            winScreen(screen, joueur2);
}
