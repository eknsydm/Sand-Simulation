#include "../headers/app.h"
#include "../headers/constants.h"
#include "../headers/draw.h"
#include "../headers/init.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: Pop the non moving sands

typedef struct InputState {
        int right;
        int left;
        int up;
        int down;
        int drop;

        int dright;
        int dleft;
        int dup;
        int ddown;
        int ddrop;

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
        Color color;
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
    newSand->color = (Color){194 + rand() % 10 - 5, 178 + rand() % 10 - 5,
                             128 + rand() % 10 - 5, 255};
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
int **initMap(int width, int height) {
    int **newMap = (int **)malloc(width * sizeof(int *));

    for (int i = 0; i < width; ++i) {
        newMap[i] = (int *)malloc(height * sizeof(int));
    }

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            *(*(newMap + x) + y) = EMPTY;
        }
    }
    return newMap;
}
int isEmpty(int ***map, int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        if ((*map)[x][y] == EMPTY) {
            return 1;
        }
    }
    return 0;
}

void moveSands(int ***map, Sand **head_ref, const int degree) {
    int down, downl, downr;
    Sand *sand = *head_ref;
    int **newMap = initMap(MAP_WIDTH, MAP_HEIGHT);
    int sandCount = 0;

    while (sand != NULL) {
        sandCount++;
        int down_x = 0;
        int down_y = 1;

        double radian = degree * (M_PI / 180);

        float down_xr = down_x * cos(radian) - down_y * sin(radian);
        float down_yr = down_x * sin(radian) + down_y * cos(radian);
        float downl_xr = (down_x - 1) * cos(radian) - down_y * sin(radian);
        float downl_yr = (down_x - 1) * sin(radian) + down_y * cos(radian);
        float downr_xr = (down_x + 1) * cos(radian) - down_y * sin(radian);
        float downr_yr = (down_x + 1) * sin(radian) + down_y * cos(radian);

        down_xr = round(down_xr);
        down_yr = round(down_yr);
        downl_xr = round(downl_xr);
        downl_yr = round(downl_yr);
        downr_xr = round(downr_xr);
        downr_yr = round(downr_yr);

        down = isEmpty(map, sand->x + down_xr, sand->y + down_yr);
        downl = isEmpty(map, sand->x + downl_xr, sand->y + downl_yr);
        downr = isEmpty(map, sand->x + downr_xr, sand->y + downr_yr);

        if (down) {
            (*map)[sand->x][sand->y] = EMPTY;
            sand->x += down_xr;
            sand->y += down_yr;
            (*map)[sand->x][sand->y] = SAND;
        } else if (downl) {
            (*map)[sand->x][sand->y] = EMPTY;
            sand->x += downl_xr;
            sand->y += downl_yr;
            (*map)[sand->x][sand->y] = SAND;
        } else if (downr) {
            (*map)[sand->x][sand->y] = EMPTY;
            sand->x += downr_xr;
            sand->y += downr_yr;
            (*map)[sand->x][sand->y] = SAND;
        }
        sand = sand->next;
    }
}

int main(void) {

    app = (App){};
    float lastFrameTime = 0;
    int **map = initMap(MAP_WIDTH, MAP_HEIGHT);
    Sand *sands_head = NULL;
    InputState input = {};
    Cursor cursor = {0, MAP_WIDTH / 2, 0, 0, 0};

    if (map == NULL) {
        printf("ERROR: map is not allocated");
    }

    int quit = 0;
    initSDL();
    int degree = 0;

    while (!quit) {

        int32_t keyCount;
        const uint8_t *keyState = SDL_GetKeyboardState(&keyCount);

        InputState prevInput = input;

        input.up = keyState[SDL_SCANCODE_W];
        input.down = keyState[SDL_SCANCODE_S];
        input.left = keyState[SDL_SCANCODE_A];
        input.right = keyState[SDL_SCANCODE_D];
        input.drop = keyState[SDL_SCANCODE_SPACE];

        input.dup = input.up - prevInput.up;
        input.ddown = input.down - prevInput.down;
        input.dleft = input.left - prevInput.left;
        input.dright = input.right - prevInput.right;
        input.ddrop = input.drop - prevInput.drop;

        if (input.dleft > 0)
            degree += 45;
        if (input.dright > 0)
            degree -= 45;
        if (input.drop > 0)
            initSand(&map, &sands_head, MAP_WIDTH / 2, 0);

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.key.keysym.sym == SDLK_ESCAPE)
                quit = 1;
            if (e.key.keysym.sym == SDLK_1)
                initSand(&map, &sands_head, MAP_WIDTH / 2, 0);
        }

        int randomx = rand() % (MAP_WIDTH / 4);
        initSand(&map, &sands_head, randomx, 0);
        moveSands(&map, &sands_head, degree);

        int time_to_wait =
            (int)FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);

        if (time_to_wait > 0 && time_to_wait < FRAME_TARGET_TIME) {
            SDL_Delay(time_to_wait);
        }

        float delta_time = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
        lastFrameTime = SDL_GetTicks();
        SDL_SetRenderDrawColor(app.renderer, 100, 100, 100, 255);
        SDL_RenderClear(app.renderer);
        drawMap(app.renderer, 20, 20, map, degree, MAP_WIDTH, MAP_HEIGHT);
        SDL_RenderPresent(app.renderer);
    }
    return 0;
}
