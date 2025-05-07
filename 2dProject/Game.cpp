#include "Game.h"

extern LWindow gWindow;
extern SDL_Renderer* gRenderer;

void Game::run()
{
    bool quit = false;
    SDL_Event e;
    //Vector of Tetrominoes that have landed on the Bottom Border or other Tetrominoes
    std::vector<Tetromino> landedTetrominoes;
    LTexture blockTexture;

    // Calculate the center position for spawning Tetrominoes
    const int startX = (SCREEN_WIDTH / BLOCK_SIZE) / 2 - 1; // Center horizontally
    const int startY = 0; // Top of the playable area


    //Spawns random Tetromino
    Tetromino currentTetromino(static_cast<TetrominoType>(rand() % 7), startX, startY);

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            gWindow.handleEvent(e);

            if (!currentTetromino.isLanded()) {
                currentTetromino.handleEvent(e, landedTetrominoes);
            }
        }

        if (!currentTetromino.isLanded()) {
            currentTetromino.update(landedTetrominoes);
        }
        else if (currentTetromino.isLanded()) {
            // Store the landed tetromino
            landedTetrominoes.push_back(currentTetromino);
            // Check for filled rows and delete them
            deleteFilledRows(landedTetrominoes);
            // Spawn new Tetromino
            currentTetromino = Tetromino(static_cast<TetrominoType>(rand() % 7), startX, startY);
        }

        //Clear Screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

		gBackgroundTexture.render(0, 0, nullptr);

        // Render landed Tetrominoes
        for (const auto& tetromino : landedTetrominoes) {
            tetromino.render(gRenderer);
        }

        //Render Tetris Shapes
        currentTetromino.render(gRenderer);

        //Update
        SDL_RenderPresent(gRenderer);
    }
}

void Game::deleteFilledRows(std::vector<Tetromino>& landedTetrominoes) {
    const int rows = SCREEN_HEIGHT / BLOCK_SIZE;
    const int cols = SCREEN_WIDTH / BLOCK_SIZE;

    // Create a grid to track filled cells
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0));

    // Fill the grid with the landed tetrominoes
    for (const auto& tetromino : landedTetrominoes) {
        const auto& shape = tetromino.getShape();
        for (int i = 0; i < shape.size(); ++i) {
            for (int j = 0; j < shape[i].size(); ++j) {
                if (shape[i][j] == 1) {
                    grid[tetromino.y + i][tetromino.x + j] = 1;
                }
            }
        }
    }

    // Collect filled rows
    std::vector<int> filledRows;
    for (int y = 0; y < rows; ++y) {
        bool isFilled = true;
        for (int x = 0; x < cols; ++x) {
            if (grid[y][x] == 0) {
                isFilled = false;
                break;
            }
        }
        if (isFilled) {
            filledRows.push_back(y);
        }
    }

    // Clear filled rows in reverse order
    for (int i = filledRows.size() - 1; i >= 0; --i) {
        int y = filledRows[i];

        // Clear the filled row in the grid
        for (int x = 0; x < cols; ++x) {
            grid[y][x] = 0;
        }

        // Remove blocks from tetrominoes that contribute to this row
        for (auto& tetromino : landedTetrominoes) {
            auto& shape = tetromino.getShape(); // Use the non-const version
            for (int i = 0; i < shape.size(); ++i) {
                for (int j = 0; j < shape[i].size(); ++j) {
                    if (shape[i][j] == 1 && tetromino.y + i == y) {
                        shape[i][j] = 0; // Remove the block
                    }
                }
            }
        }
    }

    // Move all tetrominoes above the cleared rows down by one
    for (auto& tetromino : landedTetrominoes) {
        for (int y : filledRows) {
            if (tetromino.y < y) {
                // Ensure we do not move tetrominoes below the grid
                if (tetromino.y + 1 < rows) {
                    tetromino.y++;
                }
            }
        }
    }

    // Remove empty Tetrominoes
    landedTetrominoes.erase(
        std::remove_if(landedTetrominoes.begin(), landedTetrominoes.end(),
            [](const Tetromino& t) { return t.isEmpty(); }),
		landedTetrominoes.end());
}