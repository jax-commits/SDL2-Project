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

const std::vector<std::vector<int>>& Tetromino::getShape() const {
    return shape;
}

std::vector<std::vector<int>>& Tetromino::getShape() {
    return shape;
}

void Tetromino::update(const std::vector<Tetromino>& landedTetrominoes) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFallTime > 500) { // Adjust fall speed (500ms per fall)
        if ((y + shape.size()) * BLOCK_SIZE < SCREEN_HEIGHT) { 
            y += fallSpeed;

            for (const auto& landed : landedTetrominoes) {
                if (collidesWith(landed)) {
                    y -= fallSpeed;
                    hasLanded = true;
                    break;
                }
            }
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

void Tetromino::rotateBack() {
    // Rotate three more times to revert the original rotation
    for (int i = 0; i < 3; i++) {
        rotate();
    }
}

void Tetromino::handleEvent(SDL_Event& e, const std::vector<Tetromino>& landedTetrominoes)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_a:
            if (x > 0) {
                Tetromino temp = *this;
                temp.x -= 1; // Move left with boundary check
                if (!temp.isOutOfBounds() && !temp.collidesWithAny(landedTetrominoes)) {
                    x -= 1;
                }
            }
            break;
        case SDLK_d:
            if ((x + shape[0].size()) * BLOCK_SIZE < SCREEN_WIDTH) {
                Tetromino temp = *this;
                temp.x += 1; // Move left with boundary check
                if (!temp.isOutOfBounds() && !temp.collidesWithAny(landedTetrominoes)) {
                    x += 1;
                }
            } // Move right with boundary check
            break;
        case SDLK_s:
            if ((y + shape[0].size()) * BLOCK_SIZE < SCREEN_HEIGHT) {
                Tetromino temp = *this;
                temp.y += 1; // Move left with boundary check
                if (!temp.collidesWithAny(landedTetrominoes)) {
                    y += 1;
                }
            }
            break;
        case SDLK_w:
            rotate(); // Rotate piece
            if (isOutOfBounds() || collidesWithAny(landedTetrominoes)) {
                rotateBack();
            }
            break;
        }
    }
}


void Tetromino::render(SDL_Renderer* gRenderer) const {
    int blockSize = BLOCK_SIZE;
    SDL_Rect block;

    block.x = 0;
    block.y = 0;
    block.w = block.h = blockSize;
    SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);

    for (int i = 0; i < shape.size(); ++i) {
        for (int j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j] == 1) {
                block.x = OFFSET_X + (x + j) * blockSize;
                block.y = OFFSET_Y + (y + i) * blockSize;
                SDL_RenderFillRect(gRenderer, &block);
            }
        }
    }
}

bool Tetromino::isLanded() const {
    return hasLanded;
}

bool Tetromino::isOutOfBounds() {
    int blockSize = BLOCK_SIZE;
    for (int i = 0; i < shape.size(); ++i) {
        for (int j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j] == 1) {
                int newX = OFFSET_X + (x + j) * blockSize;
                int newY = OFFSET_Y + (y + i) * blockSize;
                if (newX < OFFSET_X || newX >= OFFSET_X + SCREEN_WIDTH || newY >= OFFSET_Y + SCREEN_HEIGHT) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Tetromino::collidesWith(const Tetromino& other) const {
    int blockSize = BLOCK_SIZE;
    for (int i = 0; i < shape.size(); ++i) {
        for (int j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j] == 1) {
                int thisX = x + j;
                int thisY = y + i;
                if (thisX < 0 || thisX >= (SCREEN_WIDTH / blockSize) || thisY >= (SCREEN_HEIGHT / blockSize)) {
                    return true;
                }
                for (int k = 0; k < other.shape.size(); ++k) {
                    for (int l = 0; l < other.shape[k].size(); ++l) {
                        if (other.shape[k][l] == 1) {
                            int otherX = other.x + l;
                            int otherY = other.y + k;
                            if (thisX == otherX && thisY == otherY) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Tetromino::collidesWithAny(const std::vector<Tetromino>& landedTetrominoes) const {
    for (const auto& landed : landedTetrominoes) {
        if (collidesWith(landed)) {
            return true; // Collision detected
        }
    }
    return false; // No collisions
}

void Tetromino::deleteRow(int row) {
    for (int i = 0; i < shape.size(); ++i) {
        if (y + i == row) {
            shape.erase(shape.begin() + i);
            y++;
            i--;
        }
    }

    // Add empty rows at the top
    while (shape.size() < 4) {
        shape.insert(shape.begin(), std::vector<int>(shape[0].size(), 0));
    }
}

bool Tetromino::isEmpty() const {
    for (const auto& row : shape) {
        for (int cell : row) {
            if (cell == 1) {
                return false;
            }
        }
    }
    return true;
}