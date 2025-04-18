#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
/*---------------------------------------------------*/

enum STATE
{
  WAITING,
  FOLLOWING,
  ATTACKING
};
typedef enum STATE STATE;

typedef struct
{
  SDL_Rect pos_depart;
  SDL_Rect pos_actuelle;
  int direction; 
  float vitesse;
  SDL_Surface *spritesheet;
  SDL_Rect pos_sprites;
  int frame;
  int frameCount; 
  int frameWidth;
  int frameHeight;

  int alive; 
  STATE state;
} Ennemi;

typedef struct
{
  char *url;
  SDL_Rect pos_img_affiche;
  SDL_Rect pos_img_ecran;
  SDL_Surface *img;
} image;

void initialiser_imageBACK(image *image);
void afficher_imageBMP(SDL_Surface *screen, image image);

void initEnnemi(Ennemi *e);
void initEnnemi1(Ennemi *e);
void afficherEnnemi(Ennemi e, SDL_Surface *screen);
void animerEnemi(Ennemi *e);
void move(Ennemi *e);
void move1(Ennemi *e);
void updateEnnemiState(Ennemi *E, int distx, int disty);
void moveEnnemi(Ennemi *e, SDL_Rect posperso);
void moveEnnemi1(Ennemi *e, SDL_Rect posperso);
void moveIA(Ennemi *E, SDL_Rect posperso);
void moveIA1(Ennemi *E, SDL_Rect posperso);
int collisuionBB(Ennemi *E, SDL_Rect posPerso);
int collisionTri(Ennemi *e, SDL_Rect posPerso);


#endif
