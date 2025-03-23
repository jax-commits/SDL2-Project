#include "Dot.h"

extern LTexture gDotTexture;

Dot::Dot( int x, int y)
{
    mPosX = x;
    mPosY = y;
    mVelX = 0;
    mVelY = 0;

    for (int i = 0; i < 20; ++i)
    {
        particles[i] = new Particle(mPosX, mPosY);
    }

    //Create the necessary SDL_Rects
    mColliders.resize(11);

    mColliders[0].w = 6;
    mColliders[0].h = 1;

    mColliders[1].w = 10;
    mColliders[1].h = 1;

    mColliders[2].w = 14;
    mColliders[2].h = 1;

    mColliders[3].w = 16;
    mColliders[3].h = 2;

    mColliders[4].w = 18;
    mColliders[4].h = 2;

    mColliders[5].w = 20;
    mColliders[5].h = 6;

    mColliders[6].w = 18;
    mColliders[6].h = 2;

    mColliders[7].w = 16;
    mColliders[7].h = 2;

    mColliders[8].w = 14;
    mColliders[8].h = 1;

    mColliders[9].w = 10;
    mColliders[9].h = 1;

    mColliders[10].w = 6;
    mColliders[10].h = 1;

    //Initialize colliders relative to position
    shiftColliders();
}

Dot::~Dot()
{
    for (int i = 0; i < 20; ++i)
    {
        delete particles[i];
    }
}

void Dot::handleEvent(SDL_Event& e)
{
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_w: mVelY -= DOT_VEL; break;
        case SDLK_s: mVelY += DOT_VEL; break;
        case SDLK_a: mVelX -= DOT_VEL; break;
        case SDLK_d: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_w: mVelY += DOT_VEL; break;
        case SDLK_s: mVelY -= DOT_VEL; break;
        case SDLK_a: mVelX += DOT_VEL; break;
        case SDLK_d: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::move(std::vector<SDL_Rect>& otherColliders, const std::vector<SDL_Rect>& wallsColliders)
{
    // Move X
    mPosX += mVelX;
    shiftColliders();

    if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH) ||
        checkCollision(mColliders, otherColliders) || checkCollision(mColliders, otherColliders) || checkCollision(mColliders, wallsColliders))
    {
        mPosX -= mVelX;
        shiftColliders();
    }

    // Move Y
    mPosY += mVelY;
    shiftColliders();

    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT) ||
        checkCollision(mColliders, otherColliders) || checkCollision(mColliders, otherColliders) || checkCollision(mColliders, wallsColliders))
    {
        mPosY -= mVelY;
        shiftColliders();
    }
}

void Dot::render()
{
    gDotTexture.render(mPosX, mPosY);
    renderParticles();
}

void Dot::renderParticles()
{
    for (int i = 0; i < 20; ++i)
    {
        if (particles[i]->isDead())
        {
            delete particles[i];
            particles[i] = new Particle(mPosX, mPosY);
        }
        particles[i]->render();
    }
}

void Dot::shiftColliders()
{
    //The row offset
    int r = 0;

    //Go through the dot's collision boxes
    for (int set = 0; set < mColliders.size(); ++set)
    {
        mColliders[set].x = mPosX + (DOT_WIDTH - mColliders[set].w) / 2;
        mColliders[set].y = mPosY + r;
        r += mColliders[set].h;
    }
}

std::vector<SDL_Rect>& Dot::getColliders()
{
    return mColliders;
}
