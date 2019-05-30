#ifndef DEF_FICHIERS
#define DEF_FICHIERS

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL_image.h"

#include "constantes.h"
#include "jeu.h"

    void finNiveau(SDL_Window* window, SDL_Renderer* renderer, int lvl);
    void infoNiveau(SDL_Window* window, SDL_Renderer* renderer, int lvl);
    int chargerNiveau(int nbL, int nbC, int niveau[][nbL], int lvl);
    void initLvl0(int nbC, int nbL, int tab[][nbL]);
    void afficher(int nbc, int nbl,int niveau[][nbl]);

#endif
