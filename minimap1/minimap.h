#ifndef MINIMAP_H_INCLUDED
#define MINIMAP_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct {
    SDL_Rect pos_minimap;
    SDL_Rect pos_player;
    SDL_Rect pos_background;
    SDL_Rect pos_perso;
    SDL_Surface *img_minimap;
    SDL_Surface *img_player;
    SDL_Surface *img_background;
    SDL_Surface *img_perso;
    int playerX;
    SDL_Surface *screenSurface;
} Minimap;

typedef struct {
    int x;
    int y;
    int w;
    int h;
    SDL_Surface *image;
} Sprite;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int X;
    int Y;
    int H;
    int W;
} Personne;

void initmap(Minimap *m);
void afficherminimap(SDL_Surface *screen, Minimap *m);
int collisionPP(Personne p, SDL_Surface *Masque);
void MAJMinimap(SDL_Rect posJoueur, Minimap *m, SDL_Rect camera, int redimensionnement);
void affichertemp(Uint32* temps, SDL_Surface* screen, TTF_Font* police);

#endif
