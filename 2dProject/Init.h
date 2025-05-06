#ifndef INIT_H
#define INIT_H

#include <vector>
#include <SDL_image.h>
#include "LTexture.h"
#include "LWindow.h"
#include "Globals.h"

extern LTexture gRedBlockTexture;
extern LTexture gBlueBlockTexture;
extern LTexture gTealBlockTexture;
extern LTexture gPurpleBlockTexture;
extern LTexture gYellowBlockTexture;
extern LTexture gOrangeBlockTexture;
extern LTexture gGreenBlockTexture;

bool init();
bool loadMedia();
void close();

#endif
