#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/app.h"
#include "../headers/constants.h"

extern App app;

void initSDL() {
    int renderer_flag, window_flags;

    renderer_flag = SDL_RENDERER_ACCELERATED;
    window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("ERROR: failed to init SDL\n");
        exit(1);
    }
    app.window = SDL_CreateWindow("Jumper", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, window_flags);
    if (app.window == NULL) {
        printf("ERROR: failed to create window\n");
        exit(1);
    }

    // TODO: Wtf is this
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    app.renderer = SDL_CreateRenderer(app.window, -1, renderer_flag);

    if (app.renderer == NULL) {
        printf("ERROR: failed to create renderer\n");
        exit(1);
    }
}

void initGame() {

}
