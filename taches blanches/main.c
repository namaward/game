#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include "tb.h"

int main() {
    SDL_Surface *screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

    Menu sousMenu;
    initSousMenu(&sousMenu);

    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            else if(event.type == SDL_KEYDOWN) {
                int input = event.key.keysym.sym;
                int action = updateSousMenu(&sousMenu, input);

                if(action == 0) {
                    
                }
                else if(action == 1) {
                    
                }
            }
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        afficherSousMenu(&sousMenu, screen);
        SDL_Flip(screen);
    }

    liberer_SousMenu(&sousMenu);
    SDL_Quit();

    return 0;
}
