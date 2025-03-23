#pragma once
#ifndef INIT_H
#define INIT_H

#include <vector>
#include <SDL_image.h>
#include "LTexture.h"
#include "Globals.h"

bool init();
bool loadMedia();
void close();
bool checkCollision(const std::vector<SDL_Rect>& a, const std::vector<SDL_Rect>& b);

#endif
