#include "Game.h"

extern SDL_Renderer* gRenderer;

void Game::run()
{
    bool quit = false;
    SDL_Event e;

    //Scene Objects
    Dot dot(0, 0);
    Dot otherDot( SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
    Walls walls;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            dot.handleEvent(e);
        }

        //Move Dot & check collision
        dot.move(otherDot.getColliders(), walls.getWalls());

        //Clear Screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        //Render walls
        walls.render(gRenderer);

        //Render Dots
        dot.render();
        otherDot.render();

        //Update
        SDL_RenderPresent(gRenderer);
    }
}
