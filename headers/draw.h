#include <SDL2/SDL.h>
#include <stdint.h>

typedef struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
} Color;

void draw_rect(SDL_Renderer *renderer, float x, float y, int width, int height,
               Color color);
void fill_rect(SDL_Renderer *renderer, float x, float y, int width, int height,
               Color color);
void draw_map(SDL_Renderer *renderer, int screen_offset_x, int screen_offset_y,
              int **map,double degree, int width, int height);

void draw_cursor(SDL_Renderer *renderer, int x, int y, int width, int height);
