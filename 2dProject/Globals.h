#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include "LTexture.h"

// Extern declarations of global variables
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern LTexture gDotTexture;
extern LTexture gRedTexture;
extern LTexture gGreenTexture;
extern LTexture gBlueTexture;
extern LTexture gShimmerTexture;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int TOTAL_PARTICLES = 20;

#endif
