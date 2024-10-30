#include <SDL2/SDL.h>
typedef struct Delegate{
    void (*logic)();
    void (*draw)();

}Delegate;

typedef struct App{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Delegate *delegate;
}App;
