#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL_image.h"

#include "constantes.h"
#include "fichiers.h"

int main (int argc, char** argv)
{
    SDL_Window *ecran=NULL;
    SDL_Surface *menu=NULL;
    SDL_Renderer *renderer=NULL;
    SDL_Texture *image = NULL;
    SDL_Event event;
    int continuer=1;

    SDL_Surface *iconSurface = IMG_Load("Navi.png");
    if(!iconSurface)
        {
            printf("Erreur de chargement de l'image : %s",SDL_GetError());
            return -1;
        }

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_CreateWindow("Shut Up Navi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetWindowIcon(ecran, iconSurface);
    menu=IMG_Load("menu.png");//chargement image dans la surface

    image = SDL_CreateTextureFromSurface(renderer, menu);//transfert de l'image vers la texture
    SDL_FreeSurface(menu);//libération de la surface qui n'est plus utile
    SDL_RenderCopy(renderer,image,NULL,NULL);//on dessine la texture image sur le rendu
    SDL_RenderPresent(renderer);// on met à jour le rendu (ex SDL Flip de la SDL 1)

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_KP_1:
                        infoNiveau(ecran, renderer, 1);
                        SDL_Delay(500);
                        finNiveau(ecran, renderer, 1);
                        continuer = 0;
                        break;
                }
                break;
        }
    }

    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ecran);
    SDL_Quit();
    return EXIT_SUCCESS;
}
