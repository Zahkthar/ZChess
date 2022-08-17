#include "MainMenuState.h"

// "Privates" variables
SDL_Color mainMenuBackgroundColor = { 30, 74, 32, 255 };

sprite playButton;
sprite optionButton;
sprite quitButton;

void initMainMenuState(SDL_Window **window, SDL_Renderer **renderer) {
    (void)window;

    // playButton
    playButton.texture = LoadTexture(*renderer, "res/Images/playButton.png");
    SDL_QueryTexture(playButton.texture, NULL, NULL, &playButton.rect.w, &playButton.rect.h);
    playButton.rect.y = (int)((0.25 * SCREEN_HEIGHT) - (playButton.rect.h / 2));

    // optionButton
    optionButton.texture = LoadTexture(*renderer, "res/Images/optionButton.png");
    SDL_QueryTexture(optionButton.texture, NULL, NULL, &optionButton.rect.w, &optionButton.rect.h);
    optionButton.rect.y = (int)((0.5 * SCREEN_HEIGHT) - (optionButton.rect.h / 2));

    // quitButton
    quitButton.texture = LoadTexture(*renderer, "res/Images/quitButton.png");
    SDL_QueryTexture(quitButton.texture, NULL, NULL, &quitButton.rect.w, &quitButton.rect.h);
    quitButton.rect.y = (int)((0.75 * SCREEN_HEIGHT) - (quitButton.rect.h / 2));
}

void exitMainMenuState() {
    SDL_DestroyTexture(playButton.texture);
    playButton.texture = NULL;

    SDL_DestroyTexture(optionButton.texture);
    optionButton.texture = NULL;

    SDL_DestroyTexture(quitButton.texture);
    quitButton.texture = NULL;
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
    if(SDL_WaitEvent(&event) != 0) {
        switch(event.type) {
            case SDL_QUIT:
                return 3; 
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == 1) { // Si clic gauche
                    // Si collision avec un bouton
                    SDL_Point buttonClickPoint = { event.button.x, event.button.y };
                    if(SDL_PointInRect(&buttonClickPoint, &playButton.rect) == SDL_TRUE) { return 1; }
                    if(SDL_PointInRect(&buttonClickPoint, &optionButton.rect) == SDL_TRUE) { return 2; }
                    if(SDL_PointInRect(&buttonClickPoint, &quitButton.rect) == SDL_TRUE) { return 3; }
                }
                break;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) { return 3; }
                break;

            default:
                break;
        }
    }

    return 0;
}

void mainMenuStateRender(SDL_Window **window, SDL_Renderer **renderer) {
    (void)window;

    SDL_SetRenderDrawColor(*renderer, mainMenuBackgroundColor.r, mainMenuBackgroundColor.g, mainMenuBackgroundColor.b, mainMenuBackgroundColor.a);
    SDL_RenderClear(*renderer);

    // Render here
    SDL_Rect playButtonDestinationRect = { playButton.rect.x, playButton.rect.y, playButton.rect.w, playButton.rect.h };
    SDL_RenderCopy(*renderer, playButton.texture, NULL, &playButtonDestinationRect);
    
    SDL_Rect optionButtonDestinationRect = { optionButton.rect.x, optionButton.rect.y, optionButton.rect.w, optionButton.rect.h };
    SDL_RenderCopy(*renderer, optionButton.texture, NULL, &optionButtonDestinationRect);
    
    SDL_Rect quitButtonDestinationRect = { quitButton.rect.x, quitButton.rect.y, quitButton.rect.w, quitButton.rect.h };
    SDL_RenderCopy(*renderer, quitButton.texture, NULL, &quitButtonDestinationRect);

    SDL_RenderPresent(*renderer);
}