#include <SDL3/SDL.h>
#include <box2d/box2d.h>

#include <stdio.h>
#include "sdl_help.hpp"
#include "error.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


int main( int argc, char* args[] )
{
    //box2d init
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
    b2WorldId worldId = b2CreateWorld(&worldDef);
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
    else
    {


        //Create window
        window = SDL_CreateWindow("Falling Sand Sim", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_MAXIMIZED);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
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

    }

    b2DestroyWorld(worldId);
	return 0;
}
