#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"

int main() {
    Uint32 temps;
    TTF_Font* police = NULL; 
    SDL_Surface *screen = NULL;
    SDL_Surface *background = NULL;
    Minimap minimap;
    SDL_Rect camera = {0, 0, 800, 600};
    int redimensionnement = 100;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
        return -1;
    }

    if (TTF_Init() != 0) {
        printf("Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    police = TTF_OpenFont("/home/nama/Bureau/minimap/arial.ttf", 24);
    if (police == NULL) {
        printf("Erreur chargement TTF font: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    screen = SDL_SetVideoMode(1944, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL) {
        printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        TTF_CloseFont(police);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    background = IMG_Load("background.jpg");
    if (background == NULL) {
        printf("Erreur lors du chargement de l'image de fond: %s\n", SDL_GetError());
        TTF_CloseFont(police);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    initmap(&minimap);

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_FreeSurface(minimap.img_minimap);
                SDL_FreeSurface(minimap.img_player);
                SDL_FreeSurface(minimap.img_perso);
                SDL_FreeSurface(background);
                TTF_CloseFont(police);
                TTF_Quit();
                SDL_Quit();
                return 0;
            }
        }

        SDL_BlitSurface(background, NULL, screen, NULL);

        MAJMinimap(minimap.pos_player, &minimap, camera, redimensionnement);
        affichertemp(&temps, screen, police);
        afficherminimap(screen, &minimap);

        SDL_Flip(screen);
        SDL_Delay(10);
    }

    return 0;
}

