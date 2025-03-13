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
const float PXPM = 32.0f;
const int SSC = 4;

float metertopixel(float m) { return m * PXPM; }
b2Vec2 metertopixel(const b2Vec2& vector) {
    b2Vec2 mtop;
    mtop.x = metertopixel(vector.x);
    mtop.y = metertopixel(vector.y);
    return mtop; 
}

float pixeltometer(float px) { return px / PXPM; }
b2Vec2 pixeltometer(const b2Vec2& vector) {
    b2Vec2 ptom;
    ptom.x = pixeltometer(vector.x);
    ptom.y = pixeltometer(vector.y);
    return ptom;
}


int main( int argc, char* args[] )
{

    //box2d init
    b2WorldDef worldDef = b2DefaultWorldDef();
    printf("Established world\n");
    worldDef.gravity = b2Vec2{ 0.0f, -9.81f };
    b2WorldId worldId = b2CreateWorld(&worldDef);
    b2Vec2 GroundSize = { SCREEN_WIDTH, 40.0f };
    b2Vec2 GroundHalfSize = { GroundSize.x * 0.5f, GroundSize.y * 0.5f };
    b2Vec2 GroundPos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - (GroundSize.y * 0.5f) };
    b2BodyId groundId = createBody(pixeltometer(GroundPos.x), pixeltometer(GroundPos.y), pixeltometer(GroundHalfSize.x), pixeltometer(GroundHalfSize.y), &worldId, false);
    printf("Established ground body\n");
    b2Vec2 DynamicSize = { 128.0f, 128.0f };
    b2Vec2 DynamicHalfSize = { DynamicSize.x * 0.5f, DynamicSize.y = 0.5f };
    b2Vec2 DynamicPos = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f }; 
    b2BodyId dynamicboxId = createBody(pixeltometer(DynamicPos.x), pixeltometer(DynamicPos.y), pixeltometer(DynamicHalfSize.x), pixeltometer(DynamicHalfSize.y),  &worldId, false);
    SDL_FRect RectGround = { GroundPos.x - GroundHalfSize.x, GroundPos.y - GroundHalfSize.y, GroundSize.x, GroundSize.y };
    SDL_FRect RectDynamicBox = { DynamicPos.x - DynamicHalfSize.x, DynamicPos.y - DynamicHalfSize.y, DynamicSize.x, DynamicSize.y };


    //b2BodyDef bodyDef = b2DefaultBodyDef();
    //bodyDef.type = b2_dynamicBody;
    //bodyDef.position = { 0.0f, 4.0f };
    //b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);
    //b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    //b2ShapeDef shapeDef = b2DefaultShapeDef();
    //shapeDef.density = 1.0f;
    //shapeDef.friction = 0.3f;
    //b2ShapeId shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
    //printf("Established box body\n");

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
            

            while (SDL_PollEvent(&e)) {
                ControlBlock(e, quit, *screenSurface);
            }
            //box2D loop
            //b2World_Step(worldId, TIMESTEP, SSC);
            const b2Vec2 DynamicBoxPos = metertopixel(b2Body_GetPosition(dynamicboxId));
            //RectDynamicBox.x = DynamicBoxPos.x - (RectDynamicBox.w * 0.5f);
            //RectDynamicBox.y = DynamicBoxPos.y - (RectDynamicBox.h * 0.5f);
            //b2Vec2 position = b2Body_GetPosition(dynamicboxId);
            b2Rot rotation = b2Body_GetRotation(dynamicboxId);
            printf("%4.2f %4.2f %4.2f\n", RectGround.x,RectGround.y, b2Rot_GetAngle(rotation));
            //sand sim loop



            //drawing
            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
            SDL_RenderClear(pRenderer);
            SDL_SetRenderDrawColor(pRenderer, 114, 89, 89, 255);
            SDL_RenderFillRect(pRenderer, &RectGround);
            SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
            SDL_RenderFillRect(pRenderer, &RectDynamicBox);

            SDL_RenderPresent(pRenderer);
            //SDL_RenderRect(pRenderer, ground);
            //controls loop
            /*
            if (!SDL_UpdateWindowSurface(window)) {
                printf("Something has happened while updating the window surface! SDL_Error: %s\n", SDL_GetError());
            }
            */
        }

        Render(pRenderer);

    }

    //b2d_clear();

	return 0;
}

void Render(SDL_Renderer* pRender) {
    //take list of objects to draw, then draw them?

}
