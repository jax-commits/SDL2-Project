#pragma once
#ifndef DOT_H
#define DOT_H

#include "Particle.h"
#include "Init.h"
#include <vector>

class Dot
{
public:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int DOT_VEL = 10;

    Dot(int x, int y);
    ~Dot();
    void handleEvent(SDL_Event& e);
    void move(std::vector<SDL_Rect>& otherColliders, const std::vector<SDL_Rect>& wallsColliders);
    void render();
    std::vector<SDL_Rect>& getColliders();

private:
    Particle* particles[ TOTAL_PARTICLES ];
    void renderParticles();
    int mPosX, mPosY;
    int mVelX, mVelY;
    std::vector<SDL_Rect> mColliders;
    void shiftColliders();
};

#endif

