#include "OptionMenuState.h"

// "Privates" Structs/Unions and Enums
typedef struct sprite {
    SDL_Texture *texture;
    SDL_Rect rect;
} sprite;

// "Privates" variables
SDL_Color gameBackgroundColor = { 30, 74, 32, 255 };

sprite chessBoard = { NULL, { 0, 0, 0, 0 } };

// Functions
void initGameState(SDL_Window **window, SDL_Renderer **renderer) {
    (void)window;
    (void)renderer;

    chessBoard.texture = LoadTexture(*renderer, "res/Images/chessBoard.png");
    SDL_QueryTexture(chessBoard.texture, NULL, NULL, &chessBoard.rect.w, &chessBoard.rect.h);
    chessBoard.rect.y = (int)((0.5 * SCREEN_HEIGHT) - (chessBoard.rect.h / 2));
}

void exitGameState() {
    SDL_DestroyTexture(chessBoard.texture);
    chessBoard.texture = NULL;
}

// Update & Render
int gameStateUpdate(SDL_Window **window, SDL_Renderer **renderer, deltaTimeClock *dtClock) {
    (void)window;
    (void)renderer;
    (void)dtClock;

    /*
     * Valeurs de retour de la fonction :
     *  - 0 -> Pas de changement d'état
     *  - 1 -> Retour au MainMenuState
     *  - 3 -> Quitter le jeu
     */

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                return 3;
                break;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) { return 1; }
                break;
            
            default:
                break;
        }
    }

    return 0;
}

void gameStateRender(SDL_Window **window, SDL_Renderer **renderer) {
    (void)window;

    SDL_SetRenderDrawColor(*renderer, gameBackgroundColor.r, gameBackgroundColor.g, gameBackgroundColor.b, gameBackgroundColor.a);
    SDL_RenderClear(*renderer);

    // Render here
    SDL_Rect chessBoardDestinationRect = { chessBoard.rect.x, chessBoard.rect.y, chessBoard.rect.w, chessBoard.rect.h };
    SDL_RenderCopy(*renderer, chessBoard.texture, NULL, &chessBoardDestinationRect);
    
    SDL_RenderPresent(*renderer);
}