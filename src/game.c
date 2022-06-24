#include "game.h"

SDL_bool isGameRunning = SDL_TRUE;

int engineInit(SDL_Window **window, SDL_Renderer **renderer) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        return -1;
    }

    *window = SDL_CreateWindow(SCREEN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(*window == NULL) {
        return -1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if(*renderer == NULL) {
        return -1;
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        return -1;
    }

    return 0;
}

void gameStart(SDL_Window **window, SDL_Renderer **renderer) {
    // Initialisation des variables
    deltaTimeClock dtClock = { 0, 0, 0 };
    enum gameState gameState = MAIN_MENU_STATE;

    initMainMenuState(window, renderer); // Initialisation manuelle car c'est toujours le premier état

    // Boucle du jeu
    while(isGameRunning == SDL_TRUE) {
        // Update deltaTime
        dtClock.nowDtMeasure = SDL_GetTicks64();
        dtClock.dt = dtClock.nowDtMeasure - dtClock.lastDtMeasure;

        if(dtClock.dt >= 1000 / FRAMERATE_TARGET) {
            dtClock.lastDtMeasure = dtClock.nowDtMeasure;

            // Update
            gameUpdate(window, renderer, &dtClock, &gameState);

            // Draw
            gameRender(window, renderer, &gameState);
        }
    }

    gameStop();
}

void gameStop() {

}

void gameUpdate(SDL_Window **window, SDL_Renderer **renderer, deltaTimeClock *dtClock, enum gameState *gameState) {
    (void)window;
    (void)renderer;
    (void)dtClock;

    int updateReturnValue = 0; // Est-ce que l'on doit chager de state ou pas ?

    switch (*gameState) {
        case MAIN_MENU_STATE:
            updateReturnValue = mainMenuStateUpdate(window, renderer, dtClock);
            // updateReturnValue = 0 quand il n'y a pas de changements de state
            // Pour l'instant on ne réagit pas à 1 et 2 car les fonctions ne sont pas encore implémentées
            if(updateReturnValue == 1) { /* exitMainMenuState();initGameState(); *gameState = GAME_STATE; */ };
            if(updateReturnValue == 2) { /* exitMainMenuState(); initOptionMenuState(); *gameState = OPTION_MENU_STATE; */ };
            if(updateReturnValue == 3) { exitMainMenuState(); isGameRunning = SDL_FALSE; };
            break;
        
        case OPTION_MENU_STATE:
            printf("Option Menu State\n");
            break;

        case GAME_STATE:
            printf("Game State\n");
            break;

        default:
            break;
    }
}

void gameRender(SDL_Window **window, SDL_Renderer **renderer, enum gameState *gameState) {
    (void)window;
    (void)renderer;

    switch (*gameState) {
        case MAIN_MENU_STATE:
            mainMenuStateRender(window, renderer);
            break;
        
        case OPTION_MENU_STATE:
            break;

        case GAME_STATE:
            break;

        default:
            break;
    }
}