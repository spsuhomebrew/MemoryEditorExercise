#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

const SCREEN_WIDTH = 640;
const SCREEN_HEIGHT = 480;

int setup(SDL_Window** window, SDL_Surface** surface);
void render(SDL_Window* window, SDL_Surface* surface, SDL_Surface* background, SDL_Surface* player, SDL_Surface* carrot, int x, int y);

int setup(SDL_Window** window, SDL_Surface** screenSurface)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return -1;
    }

    *window = SDL_CreateWindow("Memory analysis Exercise #1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }

    *screenSurface = SDL_GetWindowSurface(*window);
    return 0;
}

void render(SDL_Window* window, SDL_Surface* surface, SDL_Surface* background, SDL_Surface* player, SDL_Surface* carrot, int x, int y)
{
    SDL_Rect playerLoc = { x, y, 48, 32 };
    SDL_Rect carrotLoc = { 20, 20, 0, 0 };
    SDL_BlitSurface(background, NULL, surface, NULL);
    SDL_BlitSurface(player, NULL, surface, &playerLoc);
    SDL_BlitSurface(carrot, NULL, surface, &carrotLoc);
    SDL_UpdateWindowSurface(window);
}

int main(int argc, char **argv)
{
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* background = SDL_LoadBMP( "background.bmp");
    SDL_Surface* player = SDL_LoadBMP("rabbit_normal.bmp");
    SDL_Surface* carrot = SDL_LoadBMP("carrot.bmp");

    // location of player
    // origin (0,0) is star location.
    int x = 4;
    int y = 4;

    if (setup(&window, &screenSurface) < 0) {
        return -1;
    }

    int quit = 0;
    int win = 0;
    while (quit == 0) {
        SDL_Event e;
        while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = 1;
                } else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP:
                            if (y > 1 || x == 0 || x == 7)
                                y--;
                            break;
                        case SDLK_DOWN:
                            if (y < 4 || x == 0 || x == 7)
                                ++y;
                            break;
                        case SDLK_LEFT:
                            if (x > 1 || y == 0 || y == 5)
                                --x;
                            break;
                        case SDLK_RIGHT:
                            if (x < 6 || y == 0 || y == 5)
                                ++x;
                            break;
                    }
                }
        }
        if (x == 0 && y == 0) {
            quit = 1;
            win = 1;
        }
        render(window, screenSurface, background, player, carrot, 20 + 80*x, 20 + 80*y);
    }
    if (win == 1)
        SDL_Delay(2000);
}