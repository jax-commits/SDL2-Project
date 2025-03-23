#include "Walls.h"

// Constructor to initialize walls
Walls::Walls()
{
    // Define the walls for the game
    mWalls = {
        { 100, 100, 600, 40 },
        { 200, 200, 40, 400 },
        { 800, 200, 40, 400 },
        { 100, 500, 600, 40 },
        { 400, 300, 300, 40 },
        { 750, 400, 40, 150 },
        { 500, 250, 40, 150 },
        { 400, 550, 40, 150 }
    };
}

std::vector<SDL_Rect> Walls::getWalls()
{
    return mWalls;
}

void Walls::render(SDL_Renderer* gRenderer)
{
    for (const SDL_Rect& wall : mWalls)
    {
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); // Black color for walls
        SDL_RenderFillRect(gRenderer, &wall);
    }
}