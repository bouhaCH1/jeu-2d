#include "fn.h"


int main(int argc, char *argv[]) {
    SDL_Surface *screen = NULL;
    SDL_Surface *backg = NULL;
    SDL_Surface *question = NULL;
    SDL_Surface *reponse = NULL;
    SDL_Surface *reponse2 = NULL;
    enigme riddle;
    SDL_Event event;
    int running = 1;
    SDL_Rect posbackg = {0, 0, 1024, 1024};
    SDL_Rect posrep1 = {138,564};
    SDL_Rect posrep2 = {614,564};
    SDL_Rect posrep3 = {386,700};
    SDL_Rect posquest = {82,71};
    SDL_Color textColor = {0, 0, 0};


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        printf("Echec d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        printf("Erreur d'initialisation de SDL_ttf : %s\n", TTF_GetError());
        return 1;
    }

    screen = SDL_SetVideoMode(1024, 1024, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen) {
        printf("Erreur de création de la fenêtre : %s\n", SDL_GetError());
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("arial.ttf", 30);
    if (!font) {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        return 1;
    }

    backg = IMG_Load("backg.png");
    reponse = IMG_Load("repSurf.png");
    reponse2 = IMG_Load("repSurf2.png");
    question = IMG_Load("questsurf.png");

    
    if (!backg || !reponse || !reponse2 || !question) {
        printf("Echec de chargement des images: %s\n", IMG_GetError());
        
        
        
        return 1;
    }


    generer(&riddle, "enigme.txt", font, textColor);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }



        affichage(screen, backg, &posbackg);
        affichage(screen,reponse,&posrep1);
        affichage(screen,reponse,&posrep2);
        affichage(screen,reponse,&posrep3);
        affichage(screen,question,&posquest);


        afficher(screen, riddle);

        SDL_Flip(screen);
    }

    liberer(&riddle);
    SDL_FreeSurface(backg);
    SDL_FreeSurface(reponse);
    SDL_FreeSurface(reponse2);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}