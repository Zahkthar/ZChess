#ifndef GAME_STATE_H_INCLUDED
#define GAME_STATE_H_INCLUDED

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "utils.h"
#include "config.h"

// Structs/Unions and Enums

// Extern Variables

// Functions
void initGameState(SDL_Window **window, SDL_Renderer **renderer);
void exitGameState();

// Update & Render
int gameStateUpdate(SDL_Window **window, SDL_Renderer **renderer, deltaTimeClock *dtClock);
void gameStateRender(SDL_Window **window, SDL_Renderer **renderer);

#endif // GAME_STATE_H_INCLUDED