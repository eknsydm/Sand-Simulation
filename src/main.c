#include "../headers/app.h"
#include "../headers/constants.h"
#include "../headers/draw.h"
#include "../headers/init.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>

#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_shape.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// TODO: Pop the non moving sands
// TODO: what if sand move again

enum DIRECTION{
    UP,
    RIGHT_UP,
    RIGHT,
    RIGHT_DOWN,
    DOWN,
    LEFT_DOWN,
    LEFT,
    LEFT_UP,
};

typedef struct InputState {
        int right;
        int left;
        int up;
        int down;
        int drop;

} InputState;

typedef struct Cursor {
        int x;
        int y;
        int selectedObject;
        int time;
        Color color;
} Cursor;

typedef struct Sand {
        int x;
        int y;
        struct Sand *next;
} Sand;

App app;
void initSand(int ***map, Sand **head_ref, int x, int y) {

    if ((*map)[x][y] != EMPTY)
        return;

    Sand *last = *head_ref;
    Sand *newSand = (Sand *)malloc(sizeof(Sand));
    newSand->x = x;
    newSand->y = y;
    newSand->next = NULL;

    (*map)[x][y] = SAND;

    if (*head_ref == NULL) {
        *head_ref = newSand;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newSand;
}

int is_empty(int ***map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        if ((*map)[x][y] == EMPTY) {
            return 1;
        }
    }
    return 0;
}

void move_sands(int ***map, Sand **head_ref, const int degree) {
    int down, downl, downr;
    Sand *sand = *head_ref;
    //TODO:down_x,y,downl_x,y,downr_x,y

    while (sand != NULL) {

        if (degree >= 45 && degree < 90) {
            downl = is_empty(map, sand->x, sand->y + 1);
            downr = is_empty(map, sand->x + 1, sand->y);
            down = is_empty(map, sand->x + 1, sand->y + 1);
            if (down) {
                (*map)[sand->x][sand->y] = EMPTY;
                sand->y += 1;
                sand->x += 1;
                (*map)[sand->x][sand->y] = SAND;

            } else if (downr) {
                (*map)[sand->x][sand->y] = EMPTY;
                sand->x += 1;
                (*map)[sand->x][sand->y] = SAND;
            } else if (downl) {
                (*map)[sand->x][sand->y] = EMPTY;
                sand->y += 1;
                (*map)[sand->x][sand->y] = SAND;
            }
        } else {
            down = is_empty(map, sand->x, sand->y + 1);
            downl = is_empty(map, sand->x - 1, sand->y + 1);
            downr = is_empty(map, sand->x + 1, sand->y + 1);

            // down
            if (down) {
                (*map)[sand->x][sand->y] = EMPTY;
                sand->y += 1;
                (*map)[sand->x][sand->y] = SAND;
            }
            // down left
            else if (downl) {
                (*map)[sand->x][sand->y] = EMPTY;
                sand->y += 1;
                sand->x -= 1;
                (*map)[sand->x][sand->y] = SAND;
            }
            // down right
            else if (downr) {
                (*map)[sand->x][sand->y] = EMPTY;
                sand->y += 1;
                sand->x += 1;
                (*map)[sand->x][sand->y] = SAND;
            }
        }
        sand = sand->next;
    }
}

int **initMap(int width, int height) {
    int **new_map = (int **)malloc(width * sizeof(int *));

    for (int i = 0; i < width; ++i) {
        new_map[i] = (int *)malloc(height * sizeof(int));
    }

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            *(*(new_map + x) + y) = EMPTY;
        }
    }
    return new_map;
}

void process_input(InputState *input) {}

int main(void) {

    app = (App){};
    float last_frame_time = 0;
    int **map = initMap(MAP_WIDTH, MAP_HEIGHT);
    Sand *sands_head = NULL;
    InputState input = {};
    Cursor cursor = {0, MAP_WIDTH / 2, 0, 0, 0};

    if (map == NULL) {
        printf("ERROR: map is not allocated");
    }

    int quit = 0;
    initSDL();
    int degree = 45;
    while (!quit) {

        // Input
        int32_t key_count;
        const uint8_t *key_state = SDL_GetKeyboardState(&key_count);

        input.up = key_state[SDL_SCANCODE_W];
        input.down = key_state[SDL_SCANCODE_S];
        input.left = key_state[SDL_SCANCODE_A];
        input.right = key_state[SDL_SCANCODE_D];
        input.drop = key_state[SDL_SCANCODE_SPACE];

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.key.keysym.sym == SDLK_ESCAPE)
                quit = 1;
            if (e.key.keysym.sym == SDLK_1)
                initSand(&map, &sands_head, MAP_WIDTH / 2, 0);
            if (e.key.keysym.sym == SDLK_2)
                degree = 0;
            if (e.key.keysym.sym == SDLK_3)
                degree = 45;

        }

        int randomx = rand() % (MAP_WIDTH / 4);
        initSand(&map, &sands_head, randomx, 0);
        //initSand(&map, &sands_head, 0, 0);
        move_sands(&map, &sands_head, degree);

        int time_to_wait =
            (int)FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

        if (time_to_wait > 0 && time_to_wait < FRAME_TARGET_TIME) {
            SDL_Delay(time_to_wait);
        }
        float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
        last_frame_time = SDL_GetTicks();
        // printf("\n");
        SDL_SetRenderDrawColor(app.renderer, 100, 100, 100, 255);
        SDL_RenderClear(app.renderer);
        draw_map(app.renderer, 10, 10, map, degree, MAP_WIDTH, MAP_HEIGHT);
        SDL_RenderPresent(app.renderer);
        // degree = degree % 360 + 1;
    }
    return 0;
}
