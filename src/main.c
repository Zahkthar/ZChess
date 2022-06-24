#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "game.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    /*
     * Initialisation de la SDL, de la fenêtre et du Renderer
     */
    if(engineInit(&window, &renderer) != 0) {
        fprintf(stderr, "Error on engineInit function : %s", SDL_GetError());
        goto Quit;
    }

    /*
     * Lancement du jeu
     */
    gameStart(&window, &renderer);
    
Quit:
    IMG_Quit();
    if(renderer != NULL) { SDL_DestroyRenderer(renderer); }
    if(window != NULL) { SDL_DestroyWindow(window); }
    SDL_Quit();

    return 0;
}