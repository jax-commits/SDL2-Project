#pragma once
#ifndef TETROMINO_H
#define TETROMINO_H

#include "Init.h"
#include <vector>
#include <SDL.h>

enum class TetrominoType { I, O, T, L, J, S, Z };
const int OFFSET_X = (WINDOW_WIDTH - SCREEN_WIDTH) / 2;
const int OFFSET_Y = (WINDOW_HEIGHT - SCREEN_HEIGHT) / 2;

class Tetromino {
public:
	Tetromino(TetrominoType type, int startX, int startY);

	bool hasLanded;
	int x, y;          // Position on the grid
	LTexture* blockTexture;

	void update(const std::vector<Tetromino>& landedTetrominoes);
	void rotate();
	void handleEvent(SDL_Event& e, const std::vector<Tetromino>& landedTetrominoes);
	void render(SDL_Renderer* gRenderer) const; // Render Tetris pieces
	void deleteRow(int row);

	const std::vector<std::vector<int>>& getShape() const;
	std::vector<std::vector<int>>& getShape();
	std::string getTexturePath() const;

	bool isLanded() const;
	bool isEmpty() const;

private:
	TetrominoType type;
	std::vector<std::vector<int>> shape;
	std::string texturePath;

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

