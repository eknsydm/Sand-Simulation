#define GRID_SIZE 4
#define MAP_WIDTH 200
#define MAP_HEIGHT 200

#define SCREEN_WIDTH MAP_WIDTH *GRID_SIZE
#define SCREEN_HEIGHT MAP_WIDTH *GRID_SIZE

#define FPS 120 
#define FRAME_TARGET_TIME (1000 / FPS)

#define ARRAY_COUNT (x)(sizeof(x) / sizeof(x[0]))
// TODO: FIX Naming convertion

enum EMapState {
    EMPTY = 0,
    SAND = 1,
    WATER = 2,
};
