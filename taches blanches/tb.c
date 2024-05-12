#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include "tb.h"
void initSousMenu(Menu *sousMenu) {
    
    sousMenu->image_bg = IMG_Load("sousmenu_bg.png");
    sousMenu->pos_bg.x = 0;
    sousMenu->pos_bg.y = 0;

    
    sousMenu->nbr_boutton = 2;

    
    sousMenu->tab[0].Img[0] = IMG_Load("button_resume_up.png");
    sousMenu->tab[0].Img[1] = IMG_Load("button_resume_down.png");
    sousMenu->tab[0].Pos.x = 100;
    sousMenu->tab[0].Pos.y = 100;
    sousMenu->tab[0].num = 0;

    sousMenu->tab[1].Img[0] = IMG_Load("button_save_up.png");
    sousMenu->tab[1].Img[1] = IMG_Load("button_save_down.png");
    sousMenu->tab[1].Pos.x = 100;
    sousMenu->tab[1].Pos.y = 150;
    sousMenu->tab[1].num = 1;

    sousMenu->num_bt_actif = 0;
}

void afficherSousMenu(Menu *sousMenu, SDL_Surface *screen) {

    SDL_BlitSurface(sousMenu->image_bg, NULL, screen, &sousMenu->pos_bg);

    for(int i = 0; i < sousMenu->nbr_boutton; i++) {
        SDL_BlitSurface(sousMenu->tab[i].Img[sousMenu->num_bt_actif == i], NULL, screen, &sousMenu->tab[i].Pos);
    }

    SDL_Flip(screen);
}
int updateSousMenu(Menu *sousMenu, int input) {
    int action = -1; 
    
   
    if (input == SDLK_DOWN) {
        sousMenu->num_bt_actif++;
        if (sousMenu->num_bt_actif >= sousMenu->nbr_boutton) {
            sousMenu->num_bt_actif = sousMenu->nbr_boutton - 1;
        }
    }
    
    else if (input == SDLK_UP) {
        sousMenu->num_bt_actif--;
        if (sousMenu->num_bt_actif < 0) {
            sousMenu->num_bt_actif = 0;
        }
    }
    
    else if (input == SDLK_RETURN) {
        
        action = sousMenu->tab[sousMenu->num_bt_actif].num;
    }
    
    return action;
}
// AJOUTEZ CETTE FOCNTION AU CODE DU MENU PRINCIPAL
void liberer_SousMenu(Menu *sousMenu) {
    if (sousMenu != NULL) {
        SDL_FreeSurface(sousMenu->image_bg);
        
        for (int i = 0; i < sousMenu->nbr_boutton; i++) {
            SDL_FreeSurface(sousMenu->tab[i].Img[0]);
            SDL_FreeSurface(sousMenu->tab[i].Img[1]);
        }
    } else {
        printf("Attention : Sous-menu est NULL, impossible de libérer les ressources.\n");
    }
}

void sauvegarde_jeu(personne p, background b, char *nomfichier) {
    FILE *fichier;
    fichier = fopen(nomfichier, "w");
    
    if(fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }
    
    fprintf(fichier, "%d %d\n", p.position.x, p.position.y);
    fprintf(fichier, "%d %d\n", b.position.x, b.position.y);
    
    fprintf(fichier, "%d %d\n", camera.position.x, camera.position.y);
    fprintf(fichier, "%d %d %f\n", score, nombre_vie, temps);
    
    for(int i = 0; i < nb_ennemis; i++) {
        fprintf(fichier, "%d %d\n", ennemis[i].position.x, ennemis[i].position.y);
    }
    
    for(int i = 0; i < nb_enigmes; i++) {
        fprintf(fichier, "%d\n", enigmes[i].resolue);
    }
    
    fclose(fichier);
}

void charger(personne *p, background *b, char *nomfichier) {
    FILE *fichier;
    fichier = fopen(nomfichier, "r");
    
    if(fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de chargement.\n");
        return;
    }
    
    fscanf(fichier, "%d %d", &p->position.x, &p->position.y);
    fscanf(fichier, "%d %d", &b->position.x, &b->position.y);
    
    fscanf(fichier, "%d %d", &camera.position.x, &camera.position.y);
    fscanf(fichier, "%d %d %f", &score, &nombre_vie, &temps);
    
    for(int i = 0; i < nb_ennemis; i++) {
        fscanf(fichier, "%d %d", &ennemis[i].position.x, &ennemis[i].position.y);
    }
    
    for(int i = 0; i < nb_enigmes; i++) {
        fscanf(fichier, "%d", &enigmes[i].resolue);
    }
    
    fclose(fichier);
}
