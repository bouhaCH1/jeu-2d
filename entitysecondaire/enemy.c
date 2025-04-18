#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "enemy.h"

void initialiser_imageBACK(image *image)
{

    image->url = "background.png";
    image->img = IMG_Load(image->url);
    if (image->img == NULL)
    {
        printf("unable to load background image %s \n", SDL_GetError());
    }
    image->pos_img_ecran.x = 0;
    image->pos_img_ecran.y = 0;

    image->pos_img_affiche.x = 0;
    image->pos_img_affiche.y = 0;

    image->pos_img_affiche.h =1060;
    image->pos_img_affiche.w =594;
}

void afficher_imageBMP(SDL_Surface *screen, image image)
{
    SDL_BlitSurface(image.img,NULL, screen, &image.pos_img_ecran);
}

void initEnnemi(Ennemi *e)
{
 
    e->pos_depart.x = 260;
    e->pos_depart.y = 100;

    e->pos_actuelle = e->pos_depart;
    e->direction = 0; 
    e->vitesse = 0;
    e->alive = 1;

    e->spritesheet = IMG_Load("bat.png");
    if (e->spritesheet == NULL)
    {
        printf("Erreur lors du chargement de la spritesheet de l'ennemi : %s\n", SDL_GetError());
    }

    e->frame = 0;
    e->frameCount = 4;
    e->frameWidth = 35;
    e->frameHeight = 55;

    e->pos_sprites.x = 0;
    e->pos_sprites.y = 0;
    e->pos_sprites.w = 200; 
    e->pos_sprites.h = 200;
    e->state = WAITING;
  
}
void initEnnemi1(Ennemi *e)
{
    
    e->pos_depart.x = 300;
    e->pos_depart.y = 300;

    e->pos_actuelle = e->pos_depart;
    e->direction = 0; 
    e->vitesse = 0;
    e->alive = 1;

    e->spritesheet = IMG_Load("bat.png");
    if (e->spritesheet == NULL)
    {
        printf("Erreur lors du chargement de la spritesheet de l'ennemi : %s\n", SDL_GetError());
    }

    e->frame = 0;
    e->frameCount = 4;
    e->frameWidth = 35;
    e->frameHeight = 55;

    e->pos_sprites.x = 0;
    e->pos_sprites.y = 0;
    e->pos_sprites.w = 200;
    e->pos_sprites.h = 200;
    e->state = WAITING;
}    

void afficherEnnemi(Ennemi e, SDL_Surface *screen)
{
    
    SDL_BlitSurface(e.spritesheet, &e.pos_sprites, screen, &e.pos_depart);
}
void animerEnemi(Ennemi *e)
{
    if (e->pos_sprites.x >= 2000)
        e->pos_sprites.x = 0;

    e->pos_sprites.x += 200;
}

void move1(Ennemi *e)
{

    if (e->pos_depart.y < 12)
        e->direction = 1; 
    else if (e->pos_depart.y > 400)
        e->direction = 0; 

    if (e->direction == 1)
        e->pos_depart.y += 10;
    if (e->direction == 0)
        e->pos_depart.y -= 10;
}
void move(Ennemi *e)
{

    if (e->pos_depart.y < 12)
        e->direction = 1; 
    else if (e->pos_depart.y > 400)
        e->direction = 0; 

    if (e->direction == 1)
        e->pos_depart.y += 7;
    if (e->direction == 0)
        e->pos_depart.y -= 7;
}
void moveEnnemi(Ennemi *e, SDL_Rect posperso)
{
    if (e->pos_depart.x > posperso.x)
    {
        e->pos_depart.x -= 3;

        if (e->pos_depart.y > posperso.y)
        {
            e->pos_depart.y -= 3;
        }
        if (e->pos_depart.y < posperso.y)
        {
            e->pos_depart.y = e->pos_depart.y + 3;
        }
    }
    if (e->pos_depart.x < posperso.x)
    {
        e->pos_depart.x = e->pos_depart.x + 3;

        if (e->pos_depart.y > posperso.y)
        {
            e->pos_depart.y -= 3;
        }
        if (e->pos_depart.y < posperso.y)
        {
            e->pos_depart.y = e->pos_depart.y + 3;
        }
    }
}
void moveEnnemi1(Ennemi *e, SDL_Rect posperso)
{
    if (e->pos_depart.x > posperso.x)
    {
        e->pos_depart.x -= 5;

        if (e->pos_depart.y > posperso.y)
        {
            e->pos_depart.y -= 5;
        }
        if (e->pos_depart.y < posperso.y)
        {
            e->pos_depart.y = e->pos_depart.y + 5;
        }
    }
    if (e->pos_depart.x < posperso.x)
    {
        e->pos_depart.x = e->pos_depart.x + 5;

        if (e->pos_depart.y > posperso.y)
        {
            e->pos_depart.y -= 5;
        }
        if (e->pos_depart.y < posperso.y)
        {
            e->pos_depart.y = e->pos_depart.y + 5;
        }
    }
}
void updateEnnemiState(Ennemi *E, int distx, int disty)
{
    if ((distx > 100) && (disty > 100))
        E->state = WAITING;
    else if (((50 < distx) && (distx < 100)) || ((50 < disty) && (disty < 100)))
        E->state = FOLLOWING;
}
void moveIA(Ennemi *E, SDL_Rect posperso)
{
    int dx, dy;
    switch (E->state)
    {
    case WAITING:

        move(E);
        break;
    case FOLLOWING:

        moveEnnemi(E, posperso);

        break;
    }
    
    dx = abs(E->pos_depart.x - posperso.x);
    dy = abs(E->pos_depart.y - posperso.y);

    updateEnnemiState(E, dx, dy);
}
void moveIA1(Ennemi *E, SDL_Rect posperso)
{
    int dx, dy;
    switch (E->state)
    {
    case WAITING:

        move1(E);
        break;
    case FOLLOWING:

        moveEnnemi1(E, posperso);

        break;
    }
    
    dx = abs(E->pos_depart.x - posperso.x);
    dy = abs(E->pos_depart.y - posperso.y);

    updateEnnemiState(E, dx, dy);
}
int collisuionBB(Ennemi *E, SDL_Rect posPerso)
{
    int i = 1;
    if (E->pos_depart.y > posPerso.y + posPerso.h) 
    {
        i = 0;
        return i;
    }
    if (E->pos_depart.x > posPerso.x + posPerso.w) 
    {
        i = 0;
        return i;
    }
    if (E->pos_depart.y + E->pos_depart.h < posPerso.y)
    {
        i = 0;
        return i;
    }
    if (E->pos_depart.x + E->pos_depart.w < posPerso.x)
    {
        i = 0;
        return i;
    }

    return i;
}
int collisionTri(Ennemi *e, SDL_Rect posPerso) {
    int estcoli;
    float R1,R2,X1,X2,D1,D2,Y1,Y2;
    X1=posPerso.x+posPerso.w/2;
    Y1=posPerso.y+posPerso.h/2;
    R1=sqrt(pow(posPerso.w/2,2)+pow(posPerso.h/2,2));
    if(posPerso.w<posPerso.h)
    {
        R1=posPerso.w/2;
    }
    else
    {
        R1=posPerso.h/2;
    }
    X2=e->pos_depart.x+e->pos_depart.w/2;
    Y2=e->pos_depart.y+e->pos_depart.h/2;
    R2=sqrt(pow(e->pos_depart.w/2,2)+pow(e->pos_depart.h/2,2));
    if(e->pos_depart.w<e->pos_depart.h)
    {
        R2=e->pos_depart.w/2;
    }
    else
    {
        R2=e->pos_depart.h/2;
    }
    D1=sqrt(pow(X2 - X1,2)+pow(Y2 - Y1,2));
    D2=R1+R2;
    if(D1<=D2)
    {
        estcoli=1;
    }
    else
    {
        estcoli=0;
    }
    return estcoli;
}
