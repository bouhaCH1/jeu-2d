#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "enemy.h"


int main(int argc, char *argv[])
{
    int loop = 1, i;
    SDL_Surface *screen;
    SDL_Event event;
    image IMAGE;
    Ennemi e;
    Ennemi e1;
    SDL_Surface *perso = IMG_Load("perso.png");
    SDL_Rect posPerso = {10, 450};
    SDL_Surface *coeur = IMG_Load("coeur.png");
    SDL_Rect poscoeur = {100, 100};
    int direction = -1;


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1)
    {
        printf("could not initialize SDL: %s \n", SDL_GetError());
        return -1;
    }

    screen = SDL_SetVideoMode(1060,594, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);

    initialiser_imageBACK(&IMAGE); 

    initEnnemi(&e);
    initEnnemi1(&e1);

    Uint32 start;
    const int FPS = 60;
    while (loop == 1)
    {
        start = SDL_GetTicks();

        afficher_imageBMP(screen, IMAGE);
        afficherEnnemi(e, screen);
        animerEnemi(&e);
        moveIA(&e, posPerso);
        SDL_BlitSurface(perso, NULL, screen, &posPerso);
        
        afficherEnnemi(e1, screen);
        animerEnemi(&e1);
        moveIA1(&e1, posPerso);

        if (direction == 1)
            posPerso.x += 20;
        if (direction == 0)
            posPerso.x -= 20;
        if (direction == 2)
            posPerso.y += 20;
        if (direction == 3)
            posPerso.y -= 20;

        if (collisionTri(&e, posPerso) == 1)
        {
            printf("Collision tri \n");
            SDL_BlitSurface(coeur, NULL, screen, &poscoeur);
        }
	if (collisuionBB(&e1, posPerso) == 1)
        {
            printf("Collision bb \n");
            }

        while (SDL_PollEvent(&event))
            switch (event.type)
            {
            case SDL_QUIT:
                loop = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    direction = 1;
                    break;
                case SDLK_LEFT:
                    direction = 0;
                    break;
                case SDLK_UP:
                    direction = 3;
                    break;
                case SDLK_DOWN:
                    direction = 2;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    direction = -1;
                    break;
                case SDLK_LEFT:
                    direction = -1;
                    break;
                case SDLK_UP:
                    direction = -1;
                    break;
                case SDLK_DOWN:
                    direction = -1;
                    break;
                }
            }

        SDL_Flip(screen);
        if (1000 / FPS > SDL_GetTicks() - start)
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
    }

    SDL_FreeSurface(IMAGE.img);

    SDL_Quit();
    return 0;
}
