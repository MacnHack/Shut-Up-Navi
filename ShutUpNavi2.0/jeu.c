#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL_image.h"

#include "fichiers.h"
#include "constantes.h"
#include "jeu.h"

void jouer(SDL_Window* window, SDL_Renderer* renderer, int nbL, int nbC, int Lvl)
{

    SDL_Texture *link[4] = {NULL}; // 4 surfaces pour 4 directions de link
    SDL_Texture *vide = NULL, *mur = NULL, *pot = NULL, *potOK = NULL, *objectif = NULL, *linkActuel = NULL;
    SDL_Rect position, positionJoueur;
    SDL_Event event;
    SDL_Surface *imageTmp = NULL;

    printf("niveau %d\n",Lvl);
    printf("%d %d\n", nbL, nbC);

    int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
    int carte[nbL][nbC]; // = {0};
    int tailleBloc;
    if (nbC < nbL-1)
    {
        tailleBloc = LARGEUR_FENETRE / nbL;
    }else{
        tailleBloc = HAUTEUR_FENETRE / nbC;
    }
    //printf("%d\n",tailleBloc);

        position.w = tailleBloc;
        position.h = tailleBloc;

    //Images
    imageTmp = IMG_Load("sable.png");
    vide = SDL_CreateTextureFromSurface(renderer, imageTmp);
    SDL_FreeSurface(imageTmp);
    imageTmp = IMG_Load("mur2.png");
    mur = SDL_CreateTextureFromSurface(renderer, imageTmp);
    SDL_FreeSurface(imageTmp);
    imageTmp = IMG_Load("Pot_PH.png");
    pot = SDL_CreateTextureFromSurface(renderer, imageTmp);
    SDL_FreeSurface(imageTmp);
    imageTmp = IMG_Load("PotOK.png");
    potOK = SDL_CreateTextureFromSurface(renderer, imageTmp);
    SDL_FreeSurface(imageTmp);
    imageTmp = IMG_Load("navijeu.png");
    objectif = SDL_CreateTextureFromSurface(renderer, imageTmp);
    SDL_FreeSurface(imageTmp);
    imageTmp = IMG_Load("link_bas.png");
    link[BAS] = SDL_CreateTextureFromSurface(renderer, imageTmp);
    SDL_FreeSurface(imageTmp);
    imageTmp = IMG_Load("link_gauche.png");
    link[GAUCHE] = SDL_CreateTextureFromSurface(renderer, imageTmp);
    SDL_FreeSurface(imageTmp);
    imageTmp = IMG_Load("link_haut.png");
    link[HAUT] = SDL_CreateTextureFromSurface(renderer, imageTmp);
    SDL_FreeSurface(imageTmp);
    imageTmp = IMG_Load("link_droit.png");
    link[DROITE] = SDL_CreateTextureFromSurface(renderer, imageTmp);
    SDL_FreeSurface(imageTmp);

    linkActuel = link[BAS]; // link sera dirigé vers le bas au départ

    //printf("%d %d\n", nbL, nbC);
    // Chargement du niveau
    if (!(chargerNiveau(nbL, nbC, carte, Lvl)))
    {
        exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau
    }

    //printf("%d %d\n", nbL, nbC);
    // Recherche de la position de link au départ
    for (i = 0 ; i < nbL ; i++)
    {
        for (j = 0 ; j < nbC ; j++)
        {
            if (carte[i][j] == LINK) // Si link se trouve à cette position
            {
                positionJoueur.x = i;
                positionJoueur.y = j;
                //printf("%d %d\n", i, j);
                carte[i][j] = VIDE;
            }
        }
    }
    while (continuer == 1)
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
                case SDLK_UP:
                    linkActuel = link[HAUT];
                    deplacerJoueur(nbL, nbC, carte, &positionJoueur, HAUT);
                    break;
                case SDLK_DOWN:
                    linkActuel = link[BAS];
                    deplacerJoueur(nbL, nbC, carte, &positionJoueur, BAS);
                    break;
                case SDLK_RIGHT:
                    linkActuel = link[DROITE];
                    deplacerJoueur(nbL, nbC, carte, &positionJoueur, DROITE);
                    break;
                case SDLK_LEFT:
                    linkActuel = link[GAUCHE];
                    deplacerJoueur(nbL, nbC, carte, &positionJoueur, GAUCHE);
                    break;
            }
                break;
        }
        //Effacage de l'écran pour du blanc
        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Selection couleur
        SDL_RenderClear(renderer); // Peigner TOUT le renderer avec la couleur
        SDL_RenderPresent(renderer);

        // Placement des objets à l'écran
        objectifsRestants = 0;
//printf("%d\n", tailleBloc);
        //printf("%d %d\n", nbL, nbC);
        for (i = 0 ; i < nbL ; i++)
        {
            for (j = 0 ; j < nbC ; j++)
            {
                position.x = i * tailleBloc;
                position.y = j * tailleBloc;

                SDL_SetRenderTarget(renderer, vide);
                SDL_RenderCopy(renderer, vide, NULL, &position);

                switch(carte[i][j])
                {
                    /*case VIDE:
                        SDL_SetRenderTarget(renderer, vide);
                        SDL_RenderCopy(renderer, vide, NULL, &position);
                        break;*/
                    case MUR:
                        SDL_SetRenderTarget(renderer, mur);
                        SDL_RenderCopy(renderer, mur, NULL, &position);
                        //printf("%d %d\n", i, j);
                        break;
                    case POT:
                        SDL_SetRenderTarget(renderer, pot);
                        SDL_RenderCopy(renderer, pot, NULL, &position);
                        break;
                    case POT_OK:
                        SDL_SetRenderTarget(renderer, potOK);
                        SDL_RenderCopy(renderer, potOK, NULL, &position);
                        break;
                    case OBJECTIF:
                        SDL_SetRenderTarget(renderer, objectif);
                        SDL_RenderCopy(renderer, objectif, NULL, &position);
                        objectifsRestants = 1;
                        break;
                }
            }
        }
        //afficher(nbC,nbL, carte);
                        //printf("%d\n", carte[9][18]);
        //printf("fin niveaux\n");

        // Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné
        if (!objectifsRestants){
            continuer = 0;
        }

        // On place le joueur à la bonne position
        position.x = positionJoueur.x * tailleBloc;
        position.y = positionJoueur.y * tailleBloc;
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, linkActuel, NULL, &position);

        // Update renderer
        SDL_RenderPresent(renderer); // Mise à jour du renderer

    }


    SDL_DestroyTexture(mur);
    SDL_DestroyTexture(pot);
    SDL_DestroyTexture(potOK);
    SDL_DestroyTexture(objectif);
    for (i = 0 ; i < 4 ; i++)
        SDL_DestroyTexture(link[i]);

}

void deplacerJoueur(int nbL, int nbC, int carte[nbL][nbC], SDL_Rect *pos, int direction){
    switch(direction)
    {
        case HAUT:
            if (pos->y - 1 < 0) // Si le joueur dépasse l'écran, on arrête
                break;
            if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur, on arrête
                break;
            // Si on veut pousser une pot, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre pot, ou la limite du monde)
            if ((carte[pos->x][pos->y - 1] == POT || carte[pos->x][pos->y - 1] == POT_OK) &&
                (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
                 carte[pos->x][pos->y - 2] == POT || carte[pos->x][pos->y - 2] == POT_OK))
                break;

            // Si on arrive là, c'est qu'on peut déplacer le joueur !
            // On vérifie d'abord s'il y a une pot à déplacer
            deplacerPot(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);

            pos->y--; // On peut enfin faire monter le joueur (oufff !)
            break;
        case BAS:
            if (pos->y + 1 >= nbL)
                break;
            if (carte[pos->x][pos->y + 1] == MUR)
                break;

            if ((carte[pos->x][pos->y + 1] == POT || carte[pos->x][pos->y + 1] == POT_OK) &&
                (pos->y + 2 >= nbL || carte[pos->x][pos->y + 2] == MUR ||
                 carte[pos->x][pos->y + 2] == POT || carte[pos->x][pos->y + 2] == POT_OK))
                break;


            deplacerPot(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);

            pos->y++;
            break;
        case GAUCHE:
            if (pos->x - 1 < 0)
                break;
            if (carte[pos->x - 1][pos->y] == MUR)
                break;

            if ((carte[pos->x - 1][pos->y] == POT || carte[pos->x - 1][pos->y] == POT_OK) &&
                (pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR ||
                 carte[pos->x - 2][pos->y] == POT || carte[pos->x - 2][pos->y] == POT_OK))
                break;


            deplacerPot(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);

            pos->x--;
            break;
        case DROITE:
            if (pos->x + 1 >= nbC)
                break;
            if (carte[pos->x + 1][pos->y] == MUR)
                break;

            if ((carte[pos->x + 1][pos->y] == POT || carte[pos->x + 1][pos->y] == POT_OK) &&
                (pos->x + 2 >= nbC || carte[pos->x + 2][pos->y] == MUR ||
                 carte[pos->x + 2][pos->y] == POT || carte[pos->x + 2][pos->y] == POT_OK))
                break;

            deplacerPot(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);

            pos->x++;
            break;
    }
}

void deplacerPot(int *premiereCase, int *secondeCase){
    if (*premiereCase == POT || *premiereCase == POT_OK)
    {
        if (*secondeCase == OBJECTIF)
        {
            *secondeCase = POT_OK;
        }
        else
        {
            *secondeCase = POT;
        }
        if (*premiereCase == POT_OK)
        {
            *premiereCase = OBJECTIF;
        }
        else
        {
            *premiereCase = VIDE;
        }
    }
}
