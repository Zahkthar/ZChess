#ifndef MAIN_MENU_STATE_H_INCLUDED
#define MAIN_MENU_STATE_H_INCLUDED

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "utils.h"
#include "config.h"

// Structs/Unions and Enums

// Extern Variables

// Functions
void initMainMenuState(SDL_Window **window, SDL_Renderer **renderer);
void exitMainMenuState();

// Update & Render
int mainMenuStateUpdate(SDL_Window **window, SDL_Renderer **renderer, deltaTimeClock *dtClock);
void mainMenuStateRender(SDL_Window **window, SDL_Renderer **renderer);

#endif // MAIN_MENU_STATE_H_INCLUDED