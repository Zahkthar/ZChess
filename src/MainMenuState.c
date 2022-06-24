#include "MainMenuState.h"

void initMainMenuState() {
    
}

int mainMenuStateUpdate(SDL_Window **window, SDL_Renderer **renderer, deltaTimeClock *dtClock) {
    (void)window;
    (void)renderer;
    (void)dtClock;

    /*
     * Valeurs de retour de la fonction :
     *  - 0 -> Pas de changement d'état
     *  - 1 -> Passage au GameState
     *  - 2 -> Passage au OptionMenuState
     *  - 3 -> Fermeture du jeu
     */

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                return 3;
                break;

            default:
                break;
        }
    }

    return 0;
}

void exitMainMenuState() {

}

void mainMenuStateRender(SDL_Window **window, SDL_Renderer **renderer) {
    (void)window;
    (void)renderer;
}