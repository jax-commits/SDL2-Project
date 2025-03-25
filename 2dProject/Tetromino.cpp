#include "Tetromino.h"

Tetromino::Tetromino(TetrominoType type, int startX, int startY)
    : type(type), x(startX), y(startY), lastFallTime(0), fallSpeed(1), hasLanded(false) {
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

void Tetromino::update() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFallTime > 500) { // Adjust fall speed (500ms per fall)
        if ((y + shape.size()) * 30 < SCREEN_HEIGHT) { 
            y += fallSpeed;
        }
        else {
            hasLanded = true; // Mark as landed when it reaches the bottom
        }
        lastFallTime = currentTime;
    }
}

void Tetromino::rotate() {
    int rows = shape.size();
    int cols = shape[0].size();
    std::vector<std::vector<int>> rotated(cols, std::vector<int>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotated[j][rows - 1 - i] = shape[i][j];
        }
    }

    shape = rotated;

    if (isOutOfBounds()) {
        rotateBack(); // Revert rotation if out of bounds
    }
}

bool Tetromino::isOutOfBounds() {
    int blockSize = 30;
    for (int i = 0; i < shape.size(); ++i) {
        for (int j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j] == 1) {
                int newX = (x + j) * blockSize;
                int newY = (y + i) * blockSize;
                if (newX < 0 || newX >= SCREEN_WIDTH || newY >= SCREEN_HEIGHT) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Tetromino::rotateBack() {
    // Rotate three more times to revert the original rotation
    for (int i = 0; i < 3; i++) {
        rotate();
    }
}

void Tetromino::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_a:
            if (x > 0) x -= 1; // Move left with boundary check
            break;
        case SDLK_d:
            if ((x + shape[0].size()) * 30 < SCREEN_WIDTH) x += 1; // Move right with boundary check
            break;
        case SDLK_r:
            rotate(); // Rotate piece
            break;
        }
    }
}


void Tetromino::render(SDL_Renderer* gRenderer) const{
    int blockSize = 30;
    SDL_Rect block;

    block.x = 0;
    block.y = 0;
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

bool Tetromino::isLanded() const {
    return hasLanded;
}