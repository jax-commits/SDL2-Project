#include "Particle.h"

extern LTexture gRedTexture, gGreenTexture, gBlueTexture, gShimmerTexture;

Particle::Particle(int x, int y)
{
    mPosX = x - 5 + (rand() % 25);
    mPosY = y - 5 + (rand() % 25);
    mFrame = rand() % 5;

    switch (rand() % 3)
    {
    case 0: mTexture = &gRedTexture; break;
    case 1: mTexture = &gGreenTexture; break;
    case 2: mTexture = &gBlueTexture; break;
    }
}

void Particle::render()
{
    mTexture->render(mPosX, mPosY);
    if (mFrame % 2 == 0)
    {
        gShimmerTexture.render(mPosX, mPosY);
    }
    mFrame++;
}

bool Particle::isDead()
{
    return mFrame > 10;
}
