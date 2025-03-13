#pragma once
#include "sandsim.hpp"
int RADIUS[3] = { 8, 16, 32 };
int radiusIncrement = 0;

bool isLeftMousePressed() {
    Uint32 mouseState = SDL_GetMouseState(NULL, NULL);
    return (mouseState & SDL_BUTTON_MASK(SDL_BUTTON_LEFT));
}

/// <summary>
/// Beta Version of Sand Paintbrush; draws colors to screen based on size of radius and mouse position.
/// </summary>
/// <param name="screen">Surface updated.</param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="radius"></param>
void SetColorOnMouseCoord(SDL_Surface* screen, float x, float y, Sim* _sim) {
    /*
    SDL_Rect paintArea;
    paintArea.w = radius;
    paintArea.h = radius;
    paintArea.x = x;
    paintArea.y = y;
    printf("Painting area at position X:%f, Y:%f\n", x, y);
    SDL_FillSurfaceRect(screen, &paintArea, SDL_MapRGB(SDL_GetPixelFormatDetails(screen->format), NULL, 255, 165, 0x00));
    */
    _sim->placeSand( floor(x), floor(y));

}

void ControlBlock(SDL_Event e, bool& quit, SDL_Surface& screenSurface, Sim* _sim, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    float xMouse, yMouse;

    switch (e.type) {
    case SDL_EVENT_QUIT:
        quit = true;
        break;

    case SDL_EVENT_KEY_DOWN:
        printf("Key has been pressed!\n");
        switch (e.key.key) {
            printf("Key scancode being read!\n");
        case SDLK_ESCAPE:
            quit = true;
            break;
        case SDLK_0:
            printf("Key 0 Pressed\n");
            _sim->placeSand(SCREEN_WIDTH * .5, SCREEN_HEIGHT * .5);
            break;
        case SDLK_1:
            printf("Key 1 Pressed\n");

            break;
        case SDLK_2:
            printf("Key 2 Pressed\n");

            break;

        case SDLK_3:
            printf("Key 3 Pressed\n");

            break;

        case SDLK_4:
            printf("Key 4 Pressed\n");

            break;
        case SDLK_LEFTBRACKET:
            if (radiusIncrement != 0)
                radiusIncrement--;
            else
                radiusIncrement = 2;
            break;
        case SDLK_RIGHTBRACKET:
            if (radiusIncrement != 2)
                radiusIncrement++;
            else
                radiusIncrement = 0;
            break;
        }
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        SDL_GetMouseState(&xMouse, &yMouse);
        SetColorOnMouseCoord(&screenSurface, xMouse, yMouse, _sim);
        printf("Mouse X: %f\n Mouse Y: %f\n", xMouse, yMouse);
        break;
    }
}