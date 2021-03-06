#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Structs/Unions and Enums
typedef struct deltaTimeClock {
    Uint64 nowDtMeasure;
    Uint64 lastDtMeasure;
    Uint64 dt;
} deltaTimeClock;

// Functions
SDL_Texture* LoadTexture(SDL_Renderer *renderer, char *path);

#endif