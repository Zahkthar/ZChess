#ifndef OPTION_MENU_STATE_HPP_INCLUDED
#define OPTION_MENU_STATE_HPP_INCLUDED

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "utils.h"
#include "config.h"

// Structs/Unions and Enums

// Extern Variables

// Functions
void initOptionMenuState(SDL_Window **window, SDL_Renderer **renderer);
void exitOptionMenuState();

// Update & Render
int optionMenuStateUpdate(SDL_Window **window, SDL_Renderer **renderer, deltaTimeClock *dtClock);
void optionMenuStateRender(SDL_Window **window, SDL_Renderer **renderer);

#endif // OPTION_MENU_STATE_HPP_INCLUDED