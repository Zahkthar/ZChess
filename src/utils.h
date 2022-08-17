#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
 * System
 */
typedef struct deltaTimeClock {
    Uint64 nowDtMeasure;
    Uint64 lastDtMeasure;
    Uint64 dt;
} deltaTimeClock;

/*
 * Grphics
 */
typedef struct sprite {
    SDL_Texture *texture;
    SDL_Rect rect;
} sprite;

SDL_Texture* LoadTexture(SDL_Renderer *renderer, char *path);

#endif