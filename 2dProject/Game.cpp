#include "Game.h"

extern SDL_Renderer* gRenderer;

void Game::run()
{
    bool quit = false;
    SDL_Event e;

    std::vector<Tetromino> landedTetrominoes;
    Tetromino currentTetromino(static_cast<TetrominoType>(rand() % 7), 0, 0);

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            if (!currentTetromino.isLanded()) {
                currentTetromino.handleEvent(e);
            }
        }

        if (!currentTetromino.isLanded()) {
            currentTetromino.update();
        }
        else {
            // Store the landed tetromino
            landedTetrominoes.push_back(currentTetromino);
            // Spawn new Tetromino
            currentTetromino = Tetromino(static_cast<TetrominoType>(rand() % 7), 0, 0);
        }

        //Clear Screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

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
