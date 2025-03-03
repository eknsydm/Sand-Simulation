#define GRID_SIZE 8
#define MAP_WIDTH 100
#define MAP_HEIGHT 100

#define SCREEN_WIDTH MAP_WIDTH *GRID_SIZE
#define SCREEN_HEIGHT MAP_WIDTH *GRID_SIZE

#define FPS 120
#define FRAME_TARGET_TIME (1000 / FPS)

#define ARRAY_COUNT (x)(sizeof(x) / sizeof(x[0]))

enum EMapState {
    EMPTY = 0,
    SAND = 1,
    WATER = 2,
};
enum EGravityDirection {
    UP,
    RIGHT_UP,
    RIGHT,
    RIGHT_DOWN,
    DOWN,
    LEFT_DOWN,
    LEFT,
    LEFT_UP,
};
