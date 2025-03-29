#pragma once
#ifndef GAME_H
#define GAME_H

#include "Tetromino.h"
#include "LWindow.h"
#include "Globals.h"

class Game
{
public:
    void run();
	void deleteFilledRows(std::vector<Tetromino>& landedTetrominoes);
};

#endif
