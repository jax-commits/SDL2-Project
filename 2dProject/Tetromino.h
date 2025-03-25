#pragma once
#ifndef TETROMINO_H
#define TETROMINO_H

#include "Init.h"
#include <vector>
#include <SDL.h>

enum class TetrominoType { I, O, T, L, J, S, Z };

class Tetromino {
public:
	Tetromino(TetrominoType type, int startX, int startY);

	void update(const std::vector<Tetromino>& landedTetrominoes);
	void rotate();
	void handleEvent(SDL_Event& e, const std::vector<Tetromino>& landedTetrominoes);
	void render(SDL_Renderer* gRenderer) const; // Render Tetris pieces


	bool isLanded() const;
	bool hasLanded;

private:
	TetrominoType type;
	std::vector<std::vector<int>> shape;
	SDL_Color color;

	int x, y;          // Position on the grid
	int fallSpeed;     // Fall speed (controlled in update)
	Uint32 lastFallTime;

	void setShape();
	void rotateBack();

	// Private Bool Functions for Collision Detection for 1: Screen Borders 2: Any other Objects
	bool isOutOfBounds();
	bool collidesWith(const Tetromino& other) const;
	bool collidesWithAny(const std::vector<Tetromino>& landedTetrominoes) const;
};

#endif // TETROMINO_H

