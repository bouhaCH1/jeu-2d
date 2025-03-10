#include "fn.h"



void generer(enigme *e, char *nomfichier, TTF_Font *font, SDL_Color coul) {
    FILE *file = fopen(nomfichier, "r");
    int riddlecount = 0;
    char tempQuest[100], tempRep1[100], tempRep2[100], tempRep3[100];
    int tempNumrep;

    srand(time(NULL));

    if (file) {
        while (fscanf(file, "%s %s %s %s %d \n ", tempQuest, tempRep1, tempRep2, tempRep3, &tempNumrep) != EOF) {
            riddlecount++;
            
        }

        if (riddlecount == 0) {
            printf("pffffffff %s\n", nomfichier);
            e->etat = -1;
            fclose(file);
            return;
        }

        fclose(file);
        file = fopen(nomfichier, "r");
        if (!file) {
            printf("Erreur lors de la réouverture du fichier %s\n", nomfichier);
            e->etat = -1;
            return;
        }

        int randomriddle = rand() % riddlecount;

        for (int i = 0; i < randomriddle; i++) {
            fscanf(file, "%s %s %s %s %d ", tempQuest, tempRep1, tempRep2, tempRep3, &tempNumrep);
           
        }

        if (fscanf(file, "%s %s %s %s %d",e->quest, e->rep1, e->rep2, e->rep3, &e->numrep) != 5) {
            printf("Erreur \n");
            e->etat = -1;
            fclose(file);
            return;
        }

        fclose(file);
    } else {
        printf("Erreur  %s\n", nomfichier);
        e->etat = -1;
        return;
    }

    e->questSurf = TTF_RenderText_Blended(font, e->quest, coul);
    e->rep1Surf = TTF_RenderText_Blended(font, e->rep1, coul);
    e->rep2Surf = TTF_RenderText_Blended(font, e->rep2, coul);
    e->rep3Surf = TTF_RenderText_Blended(font, e->rep3, coul);

    if (!e->questSurf || !e->rep1Surf || !e->rep2Surf || !e->rep3Surf) {
        printf("Erreur : %s\n", TTF_GetError());
        e->etat = -1;
    } else {
        e->etat = 0;  
    }

    e->questPos.x = 102;  e->questPos.y = 91;    
    e->rep1Pos.x = 168;  e->rep1Pos.y = 584;   
    e->rep2Pos.x = 649;  e->rep2Pos.y = 584;   
    e->rep3Pos.x = 400;  e->rep3Pos.y = 715;   

    e->coul = coul;
    e->font = font;
}


void afficher(SDL_Surface *screen, enigme e) {
    if (e.etat == 0) {  
        SDL_BlitSurface(e.questSurf, NULL, screen, &e.questPos);
        SDL_BlitSurface(e.rep1Surf, NULL, screen, &e.rep1Pos);
        SDL_BlitSurface(e.rep2Surf, NULL, screen, &e.rep2Pos);
        SDL_BlitSurface(e.rep3Surf, NULL, screen, &e.rep3Pos);
    }
}

void affichage(SDL_Surface *ecran, SDL_Surface *image, SDL_Rect *posecranimg) {
    if (image) {
        SDL_BlitSurface(image, NULL, ecran, posecranimg);
    }
}

void liberer(enigme *e) {
    if (e->questSurf) SDL_FreeSurface(e->questSurf);
    if (e->rep1Surf) SDL_FreeSurface(e->rep1Surf);
    if (e->rep2Surf) SDL_FreeSurface(e->rep2Surf);
    if (e->rep3Surf) SDL_FreeSurface(e->rep3Surf);
}