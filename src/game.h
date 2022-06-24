#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "MainMenuState.h"
#include "OptionMenuState.h"
#include "GameState.h"

#include "utils.h"
#include "config.h"

// Structs/Unions and Enums
enum gameState {
    MAIN_MENU_STATE,
    OPTION_MENU_STATE,
    GAME_STATE
};

// Extern Variables

// Functions
int engineInit(SDL_Window **window, SDL_Renderer **renderer); // Initialisation of SDL, SDL_image, etc...
void gameStart(SDL_Window **window, SDL_Renderer **renderer);
void gameStop(); // free tous les truc qui ont été malloc, etc...

// Update & Render
void gameUpdate(SDL_Window **window, SDL_Renderer **renderer, deltaTimeClock *dtClock, enum gameState *gameState);
void gameRender(SDL_Window **window, SDL_Renderer **renderer, enum gameState *gameState);

#endif