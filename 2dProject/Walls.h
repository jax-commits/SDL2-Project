#pragma once
#ifndef WALLS_H
#define WALLS_H

#include <vector>
#include <SDL.h>

class Walls
{
public:
    Walls();  // Constructor to initialize walls
    void render(SDL_Renderer* gRenderer);  // Render all walls
    std::vector<SDL_Rect> getWalls();

private:
    std::vector<SDL_Rect> mWalls;  // Container for all the walls
};

#endif // WALLS_H