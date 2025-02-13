#include <SDL3/SDL.h>
#include "rigidbodysim.hpp"

#include <stdio.h>
#include "sdl_help.hpp"
#include "error.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Renderer* pRenderer = nullptr;

void Render(SDL_Renderer* renderer);


int main( int argc, char* args[] )
{

    b2d_init();

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
    else
    {
        SDL_Window* window = NULL;
        SDL_Surface* screenSurface = NULL;
        //Create window
        window = SDL_CreateWindow("Falling Sand Sim", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_MAXIMIZED);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        pRenderer = SDL_CreateRenderer(window, NULL);
        //Get window surface
        screenSurface = SDL_GetWindowSurface(window);

        //Fill the surface black
        SDL_FillSurfaceRect(screenSurface, NULL, SDL_MapRGB(SDL_GetPixelFormatDetails(screenSurface->format), NULL, 0x00, 0x00, 0x00));

        //Update the surface
        SDL_UpdateWindowSurface(window);


        SDL_Event e; bool quit = false; 
        while (quit == false) {
        //main event loop
            //box2D loop


            //sand sim loop


            //controls loop
            while (SDL_PollEvent(&e)) {
                ControlBlock(e, quit, *screenSurface);
            }

            if (!SDL_UpdateWindowSurface(window)) {
                printf("Something has happened while updating the window surface! SDL_Error: %s\n", SDL_GetError());
            }
        }

        Render(pRenderer);

    }

    b2d_clear();

	return 0;
}

void Render(SDL_Renderer* pRender) {
    //take list of objects to draw, then draw them?

}
