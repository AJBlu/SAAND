#include <SDL3/SDL.h>
#include <stdio.h>
#include "sdl_help.hpp"
#include "error.hpp"
#include "rigidbodysim.h"

//origin points
const float GROUND_X = 0.0f;
const float GROUND_Y = 0.0f;
//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Renderer* pRenderer = nullptr;

void Render(SDL_Renderer* renderer);
const float TIMESTEP = 1.0f / 60.0f;
const float PXPM = 128.0f;
const int SSC = 4;

float m_to_px(float m) { return m * PXPM; }

float px_to_m(float px) { return px / PXPM; }

b2WorldId worldId;
b2BodyId bodyId;
b2BodyId groundId;


int main( int argc, char* args[] )
{

    //box2d init
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ 0.0f, -9.81f };
    worldId = b2CreateWorld(&worldDef);

    printf("Established world");
    //line body
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = { 0.0f, -10.0f };
    groundId = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);
    printf("Established ground body\n");


    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = { 0.0f, 4.0f };
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);
    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;
    b2ShapeId shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
    printf("Established box body\n");

    //b2Vec2 groundExtent = { px_to_m(SCREEN_WIDTH), px_to_m(SCREEN_HEIGHT / 2.0f) };
    //shape for body
    //b2Polygon box = b2MakeBox(groundExtent.x, groundExtent.y);


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
            printf("Timestep\n");
            b2World_Step(worldId, TIMESTEP, SSC);
            b2Vec2 position = b2Body_GetPosition(bodyId);
            b2Rot rotation = b2Body_GetRotation(bodyId);
            printf("%4.2f %4.2f %4.2f\n", position.x, position.y, b2Rot_GetAngle(rotation));
            //sand sim loop
            


            //drawing
            SDL_RenderClear(pRenderer);
            SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 0);
            SDL_FRect *ground = { 0.0, m_to_px(10.0), m_to_px(100.0), m_to_px(20.0) };
            SDL_RenderRect(pRenderer, ground);
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

    //b2d_clear();

	return 0;
}

void Render(SDL_Renderer* pRender) {
    //take list of objects to draw, then draw them?

}
