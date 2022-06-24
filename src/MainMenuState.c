#include "MainMenuState.h"

// "Privates" variables
SDL_Color backgroundColor = { 30, 74, 32, 255 };

menuButton playButton;
menuButton optionButton;
menuButton quitButton;

void initMainMenuState(SDL_Window **window, SDL_Renderer **renderer) {
    (void)window;

    // playButton
    playButton.texture = LoadTexture(*renderer, "res/Images/playButton.png");
    SDL_QueryTexture(playButton.texture, NULL, NULL, &playButton.w, &playButton.h);
    playButton.y = (int)((0.25 * SCREEN_HEIGHT) - (playButton.h / 2));

    // optionButton
    optionButton.texture = LoadTexture(*renderer, "res/Images/optionButton.png");
    SDL_QueryTexture(optionButton.texture, NULL, NULL, &optionButton.w, &optionButton.h);
    optionButton.y = (int)((0.5 * SCREEN_HEIGHT) - (optionButton.h / 2));

    // quitButton
    quitButton.texture = LoadTexture(*renderer, "res/Images/quitButton.png");
    SDL_QueryTexture(quitButton.texture, NULL, NULL, &quitButton.w, &quitButton.h);
    quitButton.y = (int)((0.75 * SCREEN_HEIGHT) - (quitButton.h / 2));
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
    SDL_DestroyTexture(playButton.texture);
    playButton.texture = NULL;

    SDL_DestroyTexture(optionButton.texture);
    optionButton.texture = NULL;

    SDL_DestroyTexture(quitButton.texture);
    quitButton.texture = NULL;
}

void mainMenuStateRender(SDL_Window **window, SDL_Renderer **renderer) {
    (void)window;

    SDL_SetRenderDrawColor(*renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderClear(*renderer);

    // Render here
    SDL_Rect playButtonDestinationRect = { playButton.x, playButton.y, playButton.w, playButton.h };
    SDL_RenderCopy(*renderer, playButton.texture, NULL, &playButtonDestinationRect);
    
    SDL_Rect optionButtonDestinationRect = { optionButton.x, optionButton.y, optionButton.w, optionButton.h };
    SDL_RenderCopy(*renderer, optionButton.texture, NULL, &optionButtonDestinationRect);
    
    SDL_Rect quitButtonDestinationRect = { quitButton.x, quitButton.y, quitButton.w, quitButton.h };
    SDL_RenderCopy(*renderer, quitButton.texture, NULL, &quitButtonDestinationRect);

    SDL_RenderPresent(*renderer);
}