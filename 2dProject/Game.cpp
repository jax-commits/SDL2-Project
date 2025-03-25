#include "Game.h"

extern LWindow gWindow;
extern SDL_Renderer* gRenderer;

void Game::run()
{
    bool quit = false;
    SDL_Event e;
    //Vector of Tetrominoes that have landed on the Bottom Border or other Tetrominoes
    std::vector<Tetromino> landedTetrominoes;

    //Spawns random Tetromino
    Tetromino currentTetromino(static_cast<TetrominoType>(rand() % 7), 0, 0);

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
