#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "constantes.h"
#include "fichiers.h"

void finNiveau(SDL_Window* window, SDL_Renderer* renderer, int lvl)
{
    SDL_Surface *GG=NULL;
    SDL_Texture *image = NULL;
    SDL_Event event;
    int continuer = 1;

    lvl++;
    //printf("%d\n", lvl);

    GG=IMG_Load("congrats.png");

    image = SDL_CreateTextureFromSurface(renderer, GG);//transfert de l'image vers la texture
    SDL_FreeSurface(GG);//libération de la surface qui n'est plus utile
    SDL_RenderCopy(renderer,image,NULL,NULL);//on dessine la texture image sur le rendu
    SDL_RenderPresent(renderer);// on met à jour le rendu


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
                        infoNiveau(window, renderer, lvl);
                        SDL_Delay(500);
                        finNiveau(window, renderer, lvl);
                        continuer = 0;
                        break;
                }
                break;
        }
    }


    SDL_DestroyTexture(image);
}

void infoNiveau(SDL_Window* window, SDL_Renderer* renderer, int lvl)
{
    int nbL, nbC, maxnbC;
    FILE* fichier = NULL;

    char level[128] = "";
    snprintf(level, sizeof level, "%d.lvl", lvl);

    fichier = fopen(level, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(-1);
    }
    else{
        char temp;
        nbL = 0, nbC = 0;

        while ((temp=fgetc(fichier)) != EOF)
        {
            if (temp == '\n')
            {
                nbL++;
                if (maxnbC < nbC)
                    {
                        maxnbC = nbC;
                    }
                nbC = 0;
            }else{
                nbC++;
            }
        }
        nbC = maxnbC;
        //printf("%d %d\n", nbL, nbC);
    }
    fclose(fichier);
    jouer(window, renderer, nbL, nbC, lvl);
}

int chargerNiveau(int nbL, int nbC, int niveau[][nbC], int lvl)
{
    FILE* fichier = NULL;
    //int i = 0, j = 0;

    initLvl0(nbC, nbL, niveau);

    char level[128] = "";
    snprintf(level, sizeof level, "%d.lvl", lvl);

    fichier = fopen(level, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
         return 0;
    }

    int temp;
    int i = 0, j = 0;
    //printf("debut map\n");
   while((temp=fgetc(fichier)) != EOF)
        {
            if(temp != '\n')
            {
                niveau[i][j] = temp - '0';
                printf("%d",niveau[i][j]);
                j++;
            }else{
                j = 0;
                i++;
                printf("\n");
            }
        }
        //}
    afficher(nbC, nbL, niveau);
    //printf("fin map\n");
    fclose(fichier);
    return 1;
}
void afficher(int nbc, int nbl,int niveau[][nbc])
{
    int i,j;
    for(i=0; i<nbl; i++)
	{
		for(j=0; j<nbc; j++)
		{
			printf("%d",niveau[i][j]);
		}
        printf("\n");

	}
}
void initLvl0(int nbC, int nbL, int tab[][nbC])
{
	int i, j;
	for(i=0; i<nbL; i++)
	{
		for(j=0; j<nbC; j++)
		{
			tab[i][j] = 0;
		}
	}
}
