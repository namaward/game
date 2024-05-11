#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include "minimap.h"

void initmap(Minimap *m) {
    if (m == NULL) {
        fprintf(stderr, "Erreur d'allocation d'espace pour minimap\n");
        exit(1);
    }

    m->img_minimap = IMG_Load("minimap.png");
    if (m->img_minimap == NULL) {
        fprintf(stderr, "Erreur chargement de minimap: %s\n", SDL_GetError());
        exit(1);
    }

    m->img_player = IMG_Load("homme.png");
    if (m->img_player == NULL) {
        fprintf(stderr, "Erreur chargement de homme: %s\n", SDL_GetError());
        exit(1);
    }

    m->img_background = IMG_Load("background.jpg");
    if (m->img_background == NULL) {
        fprintf(stderr, "Erreur chargement de l'image de fond: %s\n", SDL_GetError());
        exit(1);
    }
    m->img_perso = IMG_Load("perso.png");
    if (m->img_perso == NULL){
        fprintf(stderr, "Erreur chargement de l'image de perso: %s\n", SDL_GetError());
        exit(1);
    }
    m->pos_minimap.x = 100;
    m->pos_minimap.y = 100;
    m->pos_perso.x = 110;
    m->pos_perso.y = 220;
    m->pos_player.x = 100;
    m->pos_player.y = 400;

    m->screenSurface = SDL_GetVideoSurface();
    if (m->screenSurface == NULL) {
        fprintf(stderr, "Erreur d'initialisation de la surface d'écran : %s\n", SDL_GetError());
        exit(1);
    }
}

void afficherminimap(SDL_Surface* screen, Minimap* m) {
    SDL_BlitSurface(m->img_minimap, NULL, screen, &m->pos_minimap);
    SDL_BlitSurface(m->img_player, NULL, screen, &m->pos_player);
    SDL_BlitSurface(m->img_perso , NULL , screen , &m->pos_perso);
}


SDL_Color GetPixel(SDL_Surface* pSurface, int x, int y) {
    SDL_Color color;
    Uint32 col = 0;
    char* pPosition = (char*)pSurface->pixels;
    pPosition += (pSurface->pitch * y);
    pPosition += (pSurface->format->BytesPerPixel * x);
    memcpy(&col, pPosition, pSurface->format->BytesPerPixel);
    
    SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);
    return color;
}

int collisionPP(Personne p, SDL_Surface *Masque) {
    int i;
    int collision = 0;

    Position points[8] = {
        {p.X, p.Y},
        {p.X + p.W / 2, p.Y},
        {p.X + p.W, p.Y},
        {p.X, p.Y + p.H / 2},
        {p.X, p.Y + p.H},
        {p.X + p.W / 2, p.Y + p.H},
        {p.X + p.W, p.Y + p.H},
        {p.X + p.W, p.Y + p.H / 2}
    };

    for (i = 0; i < 8 && collision == 0; i++) {
        Uint8 r, g, b;
        SDL_Color obstacleColor = GetPixel(Masque, points[i].x, points[i].y);
        SDL_GetRGB(SDL_MapRGB(Masque->format, obstacleColor.r, obstacleColor.g, obstacleColor.b), Masque->format, &r, &g, &b);
        if (r == 0 && g == 0 && b == 0) {
            collision = 1;
        }
    }

    return collision;
}

void MAJMinimap(SDL_Rect posJoueur, Minimap *m, SDL_Rect camera, int redimensionnement) {
    SDL_Rect posJoueurABS;
    posJoueurABS.x = posJoueur.x + camera.x;
    posJoueurABS.y = posJoueur.y + camera.y;
    m->pos_player.x = (posJoueurABS.x * redimensionnement) / 100;
    m->pos_player.y = (posJoueurABS.y * redimensionnement) / 100;
}


void affichertemp(Uint32 *temps, SDL_Surface *screen, TTF_Font *police) {
    SDL_Surface *chrono = NULL;
    SDL_Rect positionChrono;
    SDL_Color couleur = {255, 255, 255};

    int min = 0, sec = 0;
    char texteChrono[10];  
    positionChrono.x = 840;
    positionChrono.y = 10;

    (*temps) = SDL_GetTicks() / 1000;
    min = (*temps) / 60;
    sec = (*temps) % 60;
    
    sprintf(texteChrono, "%02d:%02d", min, sec);

    chrono = TTF_RenderText_Solid(police, texteChrono, couleur);

    if (chrono != NULL) {
        SDL_BlitSurface(chrono, NULL, screen, &positionChrono);
        SDL_FreeSurface(chrono); 
    } else {
        fprintf(stderr, "Failed to render chrono text: %s\n", TTF_GetError());
    }
}
