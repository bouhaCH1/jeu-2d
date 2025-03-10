#ifndef FN_H
#define FN_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct {
    char quest[100];   
    char rep1[100];    
    char rep2[100];    
    char rep3[100];    
    int numrep;        
    int etat;          
    SDL_Surface *questSurf;  
    SDL_Surface *rep1Surf;   
    SDL_Surface *rep2Surf; 
    SDL_Surface *rep3Surf;   
    SDL_Rect questPos;       
    SDL_Rect rep1Pos;        
    SDL_Rect rep2Pos;        
    SDL_Rect rep3Pos;        
    SDL_Color coul;          
    TTF_Font *font;       
} enigme;


void generer(enigme *e, char *nomfichier, TTF_Font *font, SDL_Color coul);
void afficher(SDL_Surface *screen, enigme riddle);
void affichage(SDL_Surface *ecran, SDL_Surface *image, SDL_Rect *posecranimg); 
void liberer(enigme *e);

#endif