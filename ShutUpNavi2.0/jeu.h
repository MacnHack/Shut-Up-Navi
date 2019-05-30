#ifndef DEF_JEU
#define DEF_JEU
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL_image.h"

#include "constantes.h"

    void jouer(SDL_Window* window, SDL_Renderer* renderer, int nbL, int nbC, int Lvl);
    void deplacerJoueur(int nbL, int nbC, int carte[nbC][nbL], SDL_Rect *pos, int direction); //[][NB_BLOCS_HAUTEUR]
    void deplacerPot(int *premiereCase, int *secondeCase);


#endif
