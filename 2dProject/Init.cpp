#include "Init.h"


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gDotTexture;
LTexture gRedTexture;
LTexture gGreenTexture;
LTexture gBlueTexture;
LTexture gShimmerTexture;

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

        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

    //Load dot texture
    if (!gDotTexture.loadFromFile("Resources/dot.bmp"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }

    //Load red texture
    if (!gRedTexture.loadFromFile("Resources/red.bmp"))
    {
        printf("Failed to load red texture!\n");
        success = false;
    }

    //Load green texture
    if (!gGreenTexture.loadFromFile("Resources/green.bmp"))
    {
        printf("Failed to load green texture!\n");
        success = false;
    }

    //Load blue texture
    if (!gBlueTexture.loadFromFile("Resources/blue.bmp"))
    {
        printf("Failed to load blue texture!\n");
        success = false;
    }

    //Load shimmer texture
    if (!gShimmerTexture.loadFromFile("Resources/shimmer.bmp"))
    {
        printf("Failed to load shimmer texture!\n");
        success = false;
    }

    //Set texture transparency
    gRedTexture.setAlpha(192);
    gGreenTexture.setAlpha(192);
    gBlueTexture.setAlpha(192);
    gShimmerTexture.setAlpha(192);

    return success;
}

void close()
{
    // Free loaded images
    gDotTexture.free();

    // Destroy window and renderer
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

//Check collision per pixel
bool checkCollision(const std::vector<SDL_Rect>& a, const std::vector<SDL_Rect>& b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    for (int Abox = 0; Abox < a.size(); Abox++)
    {
        leftA = a[Abox].x;
        rightA = a[Abox].x + a[Abox].w;
        topA = a[Abox].y;
        bottomA = a[Abox].y + a[Abox].h;

        for (int Bbox = 0; Bbox < b.size(); Bbox++)
        {
            leftB = b[Bbox].x;
            rightB = b[Bbox].x + b[Bbox].w;
            topB = b[Bbox].y;
            bottomB = b[Bbox].y + b[Bbox].h;

            if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
            {
                return true;
            }
        }
    }
    return false;
}