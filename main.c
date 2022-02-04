#include "SDL.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 480

static SDL_Window *window;
static SDL_bool done = SDL_FALSE;

typedef struct _Line {
    struct _Line *next;

    int x1, y1, x2, y2;
    Uint8 r, g, b;
} Line;

static Line *active = NULL;
//static Line *lines =NULL;
//static int buttons = 0;

void DrawLine(SDL_Renderer *renderer, Line *line)
{
    SDL_SetRenderDrawColor(renderer, line->r, line->g, line->b, 255);
    SDL_RenderDrawLine(renderer, line->x1, line->y1, line->x2, line->y2);
}

void loop(void *arg)
{
    SDL_Renderer *renderer = (SDL_Renderer *)arg;
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {

        case SDL_QUIT:
            done = SDL_TRUE;
            break;

        default:
            break;
        }
    }
    if(!active){
        active = SDL_calloc(1, sizeof(Line));
    }


    SDL_SetRenderDrawColor(renderer, 51, 76, 76, 255);
    SDL_RenderClear(renderer);


    active->x1 = 20;
    active->y1 = 20;

    active->x2 = 99;
    active->y2 = 99;

    active->r = 255;
    active->g = 0;
    active->b = 0;

    DrawLine(renderer, active);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawPoint(renderer, 10, 10);


    SDL_RenderPresent(renderer);
    //done=SDL_TRUE;
}

int main(int argc, char **argv)
{
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, 0);

    renderer = SDL_CreateRenderer(window, -1, 0);
    while(!done) {
        loop(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}
