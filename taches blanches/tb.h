#ifndef TB_H_INCLUDED
#define TB_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct {
    SDL_Surface* Img[2];
    SDL_Rect Pos;
    Mix_Chunk *son;
    int num;  
} Boutton;

typedef struct {
    SDL_Surface * image_bg;
    SDL_Rect pos_bg;
    int nbr_boutton;  
    Boutton tab[10];
    Mix_Music *musique;
    int num_bt_actif;  
} Menu;

#endif
