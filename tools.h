#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

void printText(SDL_Surface *screen, char text[], int x, int y, char police[], int sz, SDL_Color color);
bool whereMoveDame(int plateau[10][10], int tableau[2], int tableau2[20][2], int tour, int pionManger[20][2]);

#endif // TOOLS_H_INCLUDED
