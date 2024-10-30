#include "../headers/draw.h"
#include "../headers/constants.h"
#include <SDL2/SDL.h>
#include <stdint.h>

void draw_rect(SDL_Renderer *renderer, int x, int y, int width, int height,
               Color color) {
    SDL_Rect rect = {};

    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &rect);
}

void fill_rect(SDL_Renderer *renderer, int x, int y, int width, int height,
               Color color) {
    SDL_Rect rect = {};

    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void draw_map(SDL_Renderer *renderer, int screen_offset_x, int screen_offset_y,
              int **map, int width, int height) {
    int x, y;
    Color _test = {20, 20, 20, 255};
    Color _yellow = {255, 120, 40, 255};
    for (x = 0; x < width; ++x) {
        for (y = 0; y < height; ++y) {
            if (map[x][y] == EMPTY) { 
                draw_rect(renderer, (screen_offset_x + x) * GRID_SIZE,
                          (screen_offset_y + y) * GRID_SIZE, GRID_SIZE,
                          GRID_SIZE, _test);
            } else if (map[x][y] == SAND) {
                fill_rect(renderer, (screen_offset_x + x) * GRID_SIZE,
                          (screen_offset_y + y) * GRID_SIZE, GRID_SIZE,
                          GRID_SIZE, _yellow);

            }
        }
    }
}
