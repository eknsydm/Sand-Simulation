#include "../headers/draw.h"
#include "../headers/constants.h"
#include <SDL2/SDL.h>
#include <math.h>

void draw_rect(SDL_Renderer *renderer, float x, float y, int width, int height,
               Color color) {
    SDL_Rect rect = {};

    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &rect);
}

void fill_rect(SDL_Renderer *renderer, float x, float y, int width, int height,
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
              int **map,double degree, int width, int height) {
    int x, y;
    float xr, yr;
    float px, py;

    Color _test = {20, 20, 20, 255};
    Color _yellow = {255, 160, 40, 255};
    double radian = degree * (M_PI / 180);  
    for (x = 0; x < width; ++x) {
        for (y = 0; y < height; ++y) {

            px = x - width / 2.0;
            py = y - height / 2.0;
    
            xr = px * cosf(radian) - py * sinf(radian);
            yr = px * sinf(radian) + py * cosf(radian);

            xr += width / 2.0;
            yr += width / 2.0;

            if (map[x][y] == EMPTY) {
                draw_rect(renderer, (screen_offset_x + xr) * GRID_SIZE,
                          (screen_offset_y + yr) * GRID_SIZE, GRID_SIZE,
                          GRID_SIZE, _test);
            } else if (map[x][y] == SAND) {
                fill_rect(renderer, (screen_offset_x + xr) * GRID_SIZE,
                          (screen_offset_y + yr) * GRID_SIZE, GRID_SIZE,
                          GRID_SIZE, _yellow);
            }
        }
    }
}
void draw_cursor(SDL_Renderer *renderer, int x, int y, int width, int height) {}
