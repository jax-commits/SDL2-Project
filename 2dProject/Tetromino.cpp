#include "Tetromino.h"

Tetromino::Tetromino(TetrominoType type, int startX, int startY)
    : type(type), x(startX), y(startY), lastFallTime(0), fallSpeed(1) {
    setShape();
}

void Tetromino::setShape() {
    switch (type) {
    case TetrominoType::I:
        shape = { {1, 1, 1, 1} };
        color = { 0, 255, 255, 255 }; // Cyan
        break;
    case TetrominoType::O:
        shape = { {1, 1}, {1, 1} };
        color = { 255, 255, 0, 255 }; // Yellow
        break;
    case TetrominoType::T:
        shape = { {0, 1, 0}, {1, 1, 1} };
        color = { 128, 0, 128, 255 }; // Purple
        break;
    case TetrominoType::L:
        shape = { {1, 0, 0}, {1, 1, 1} };
        color = { 255, 165, 0, 255 }; // Orange
        break;
    case TetrominoType::J:
        shape = { {0, 0, 1}, {1, 1, 1} };
        color = { 0, 0, 255, 255 }; // Blue
        break;
    case TetrominoType::S:
        shape = { {0, 1, 1}, {1, 1, 0} };
        color = { 0, 255, 0, 255 }; // Green
        break;
    case TetrominoType::Z:
        shape = { {1, 1, 0}, {0, 1, 1} };
        color = { 255, 0, 0, 255 }; // Red
        break;
    }
}

void Tetromino::move(int dx) {
    x += dx;
}

void Tetromino::update() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFallTime > 500) { // Adjust fall speed (500ms per fall)
        y += fallSpeed;
        lastFallTime = currentTime;
    }
}

void Tetromino::rotate() {
    int size = shape.size();
    std::vector<std::vector<int>> rotated(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            rotated[j][size - 1 - i] = shape[i][j];

    shape = rotated;
}

void Tetromino::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_a:
            x -= 1; // Move left
            break;
        case SDLK_d:
            x += 1; // Move right
            break;
        case SDLK_r:
            rotate(); // Rotate piece
            break;
        }
    }
}

void Tetromino::render(SDL_Renderer* gRenderer) {
    int blockSize = 50;
    SDL_Rect block;

    block.w = block.h = blockSize;
    SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);

    for (int i = 0; i < shape.size(); ++i) {
        for (int j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j] == 1) {
                block.x = (x + j) * blockSize;
                block.y = (y + i) * blockSize;
                SDL_RenderFillRect(gRenderer, &block);
            }
        }
    }
}

std::vector<SDL_Rect> Tetromino::getBlocks() const {
    std::vector<SDL_Rect> blocks;
    int blockSize = 30;

    for (int i = 0; i < shape.size(); ++i) {
        for (int j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j]) {
                SDL_Rect rect = { (x + j) * blockSize, (y + i) * blockSize, blockSize, blockSize };
                blocks.push_back(rect);
            }
        }
    }

    return blocks;
}