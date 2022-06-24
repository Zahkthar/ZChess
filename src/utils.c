#include "utils.h"

SDL_Texture* LoadTexture(SDL_Renderer *renderer, char *path) {
    SDL_Texture *texture = NULL;

    texture = IMG_LoadTexture(renderer, path);
    if(texture == NULL) {
        printf("Unable to create texture from %s. Error : %s\n", path, SDL_GetError());
        return NULL;
    }

    return texture;
}