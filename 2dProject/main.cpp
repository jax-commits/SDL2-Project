#include "Game.h"

int main(int argc, char* args[])
{
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            Game game;
            game.run();
        }
    }

    close();
    return 0;
}
