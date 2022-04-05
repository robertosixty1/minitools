#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WIDTH  800
#define HEIGHT 600

void scc(int code)
{
    if (code < 0)
    {
        fprintf(stderr, "ERROR: The graphics framework throw an error: %s\n", SDL_GetError());
        exit(1);
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "ERROR: No argument provided\n");
        fprintf(stderr, "    usage: miniviewer <file>\n");
        exit(1);
    }

    const char* file_path = argv[1];

    int x,y,n;
    unsigned char *image_data = stbi_load(file_path, &x, &y, &n, 0);
    stbi_image_free(image_data);

    if (image_data == NULL)
    {
        fprintf(stderr, "ERROR: Invalid image\n");
        exit(1);
    }

    scc(SDL_Init(SDL_INIT_VIDEO));
    scc(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP));

    SDL_Event event;
    SDL_Window* window = SDL_CreateWindow("miniviewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface* image = IMG_Load(file_path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // image rect
    SDL_Rect imagesrc_rect = {
         .x = WIDTH/2 - x/2,
         .y = HEIGHT/2 - y/2,
         .w = x,
         .h = y,
    };

    float scale_change    = 1.2;
    float position_change = 30;

    bool quit = false;
    while (!quit)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {

        case SDL_QUIT: {
            quit = true;
        } break;

        case SDL_KEYDOWN: {
            switch (event.key.keysym.sym)
            {

            case SDLK_DOWN: {
                if (imagesrc_rect.h > 500)
                {
                    imagesrc_rect.w /= scale_change;
                    imagesrc_rect.h /= scale_change;
                }
            } break;

            case SDLK_UP: {
                if (imagesrc_rect.h < 1500)
                {
                    imagesrc_rect.w *= scale_change;
                    imagesrc_rect.h *= scale_change;
                }
            } break;

            case SDLK_d: {
                imagesrc_rect.x -= position_change;
            } break;

            case SDLK_a: {
                imagesrc_rect.x += position_change;
            } break;

            case SDLK_s: {
                imagesrc_rect.y -= position_change;
            } break;

            case SDLK_w: {
                imagesrc_rect.y += position_change;
            } break;

            }
        } break;

        }

        scc(SDL_RenderCopy(renderer, texture, NULL, &imagesrc_rect));
        SDL_RenderPresent(renderer);

        scc(SDL_RenderClear(renderer));
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(image);

    IMG_Quit();
    SDL_Quit();
    return 0;
}
