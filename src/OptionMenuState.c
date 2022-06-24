#include "OptionMenuState.h"

typedef struct menuButton {
    SDL_Texture *texture;
    SDL_Rect rect;
} menuButton;

// "Privates" variables
SDL_Color optionMenuBackgroundColor = { 30, 74, 32, 255 };

menuButton returnButton;

void initOptionMenuState(SDL_Window **window, SDL_Renderer **renderer) {
    (void)window;

    // playButton
    returnButton.texture = LoadTexture(*renderer, "res/Images/returnButton.png");
    SDL_QueryTexture(returnButton.texture, NULL, NULL, &returnButton.rect.w, &returnButton.rect.h);
    returnButton.rect.y = SCREEN_HEIGHT - returnButton.rect.h;
}

void exitOptionMenuState() {
    SDL_DestroyTexture(returnButton.texture);
    returnButton.texture = NULL;
}

int optionMenuStateUpdate(SDL_Window **window, SDL_Renderer **renderer, deltaTimeClock *dtClock) {
    (void)window;
    (void)renderer;
    (void)dtClock;

    /*
     * Valeurs de retour de la fonction :
     *  - 0 -> Pas de changement d'état
     *  - 1 -> Retour au MainMenuState
     */

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                return 3;
                break;

            case SDL_MOUSEBUTTONUP:
                if(event.button.button == 1) { // Si clic gauche
                    // Si collision avec un bouton
                    SDL_Point buttonClickPoint = { event.button.x, event.button.y };
                    if(SDL_PointInRect(&buttonClickPoint, &returnButton.rect) == SDL_TRUE) { return 1; }
                }
                break;

            default:
                break;
        }
    }

    return 0;
}

void optionMenuStateRender(SDL_Window **window, SDL_Renderer **renderer) {
    (void)window;

    SDL_SetRenderDrawColor(*renderer, optionMenuBackgroundColor.r, optionMenuBackgroundColor.g, optionMenuBackgroundColor.b, optionMenuBackgroundColor.a);
    SDL_RenderClear(*renderer);

    // Render here
    SDL_Rect returnButtonDestinationRect = { returnButton.rect.x, returnButton.rect.y, returnButton.rect.w, returnButton.rect.h };
    SDL_RenderCopy(*renderer, returnButton.texture, NULL, &returnButtonDestinationRect);

    SDL_RenderPresent(*renderer);
}