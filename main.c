#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_mouse.h"
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "SDL3/SDL_video.h"
#include "lot.h"

#define WIDTH 1080
#define HEIGHT 720 

int Isover(SDL_FRect *square, int x, int y){
    if (x >= square->x && x <= square->x + square->w && y >= square->y && y <= square->y + square->h){
        return true;
    }
    return false;
}

int main(int argc, char **argv){
    SDL_Init(SDL_INIT_VIDEO);
    bool done = false;
    bool w_held = false;
    bool s_held = false;
    bool a_held = false;
    bool d_held = false;
    int win_width;
    int win_height;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Event event;
    window = SDL_CreateWindow("idk lol", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if (window == NULL){
        SDL_Quit();
    }
    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL){
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    SDL_FRect square = {WIDTH / 2 - 50, HEIGHT / 2 - 50, 100, 100};
    do {
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_EVENT_QUIT:
                done = true;
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                if (event.button.button == SDL_BUTTON_LEFT){
                    int x = event.button.x;
                    int y = event.button.y;
                    if (Isover(&square, x, y)){
                        lot l = Lot();
                        Writelot(&l);
                    }
                }
                break;
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_ESCAPE){
                    done = true;
                }
                if (event.key.key == SDLK_W){
                    w_held = true;
                }
                if (event.key.key == SDLK_S){
                    s_held = true;
                }
                if (event.key.key == SDLK_A){
                    a_held = true;
                }
                if (event.key.key == SDLK_D){
                    d_held = true;
                }
                break;
            case SDL_EVENT_KEY_UP:
                if (event.key.key == SDLK_W){
                    w_held = false;
                }
                if (event.key.key == SDLK_S){
                    s_held = false;
                }
                if (event.key.key == SDLK_A){
                    a_held = false;
                }
                if (event.key.key == SDLK_D){
                    d_held = false;
                }
                break;

        }
        SDL_GetWindowSizeInPixels(window, &win_width, &win_height);
        if (w_held){
            if (a_held || d_held){
                square.y += 5;
            }
            if (square.y - 10 >= 0) square.y -= 10;
        }
        if (s_held){
            if (a_held || d_held){
                square.y -= 5;
            }
            if (square.y + square.h + 10 <= win_height){
                square.y += 10;
            }
        }
        if (a_held){
            if (s_held || w_held){
                square.x += 5;
            }
            if (square.x - 10 >= 0) square.x -= 10;
        }
        if (d_held){
            if (s_held || w_held){
                square.x -= 5;
            }
            if (square.x + square.w + 10 <= win_width){
                square.x += 10;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &square);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    while(!done);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
