#include "Init.h"

LWindow gWindow;
SDL_Renderer* gRenderer = nullptr;
LTexture gRedBlockTexture;
LTexture gBlueBlockTexture;
LTexture gTealBlockTexture;
LTexture gPurpleBlockTexture;
LTexture gYellowBlockTexture;
LTexture gOrangeBlockTexture;
LTexture gGreenBlockTexture;
LTexture gBackgroundTexture;

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        if (!gWindow.init())
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = gWindow.createRenderer();
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    if (!gBlueBlockTexture.loadFromFile("Resources/blueTetromino.png"))
    {
        printf("Failed to load blue block texture!\n");
        success = false;
    }

    if (!gRedBlockTexture.loadFromFile("Resources/redTetromino.png"))
    {
        printf("Failed to load red block texture!\n");
        success = false;
    }

    if (!gGreenBlockTexture.loadFromFile("Resources/greenTetromino.png"))
    {
        printf("Failed to load green block texture!\n");
        success = false;
    }

    if (!gYellowBlockTexture.loadFromFile("Resources/yellowTetromino.png"))
    {
        printf("Failed to load yellow block texture!\n");
        success = false;
    }

    if (!gOrangeBlockTexture.loadFromFile("Resources/orangeTetromino.png"))
    {
        printf("Failed to load orange block texture!\n");
        success = false;
    }

    if (!gTealBlockTexture.loadFromFile("Resources/tealTetromino.png"))
    {
        printf("Failed to load teal block texture!\n");
        success = false;
    }

    if (!gPurpleBlockTexture.loadFromFile("Resources/purpleTetromino.png"))
    {
        printf("Failed to load purple block texture!\n");
        success = false;
    }

    if (!gBackgroundTexture.loadFromFile("Resources/TetrisBackground.png"))
    {
        printf("Failed to load background texture!\n");
        success = false;
    }

    //Set texture transparency
    gRedBlockTexture.setAlpha(255);
    gBlueBlockTexture.setAlpha(255);
    gGreenBlockTexture.setAlpha(255);
    gYellowBlockTexture.setAlpha(255);
    gOrangeBlockTexture.setAlpha(255);
    gPurpleBlockTexture.setAlpha(255);
    gTealBlockTexture.setAlpha(255);
	gBackgroundTexture.setAlpha(255);

    return success;
}

void close()
{
    gRedBlockTexture.free();
    gBlueBlockTexture.free();
    gGreenBlockTexture.free();
    gYellowBlockTexture.free();
    gOrangeBlockTexture.free();
    gPurpleBlockTexture.free();
    gTealBlockTexture.free();
	gBackgroundTexture.free();

    // Destroy window and renderer
    SDL_DestroyRenderer(gRenderer);
    gWindow.free();

    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}