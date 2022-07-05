#include "Headers/game.h"
#include "Headers/gamemanager.h"

SDL_Texture* wingTex;
GameManager gameManager;
SDL_Surface* surf = IMG_Load("DevAssets/Textures/colonel.png");

Game::Game()
{
    window = nullptr;
    renderer = nullptr;
    screenHeight = 600;
    screenWidth = 1024;
    gameState = GameState::PLAY;
};

Game::~Game() {};

// Called at launch.
void Game::Run()
{
    Init("Please stop ordering Jumbo Bkts.", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    Begin();
    while (gameState != GameState::EXIT) Forever();
}

// Init window and renderer.
void Game::Init(const char* title, int x, int y, int w, int h, Uint32 flags)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(title, x, y, w, h, flags);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 224, 57, 45, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    
    SDL_Surface* surf = IMG_Load("DevAssets/Textures/namjas.bmp");
}

// Called at start of game.
void Game::Begin()
{
    SDL_BlitSurface(surf, NULL, NULL, NULL);
    Debug("game");
}

// Game loop.
void Game::Forever()
{
    HandleEvents();
}

// Event handler.
void Game::HandleEvents()
{
    SDL_Event evnt;
    SDL_PollEvent(&evnt);

    switch (evnt.type)
    {
        case SDL_QUIT:
            gameState = GameState::EXIT;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (evnt.button.button == SDL_BUTTON_LEFT)
            {
                gameManager.PlayerAction();
                Debug(std::to_string(gameManager.score) + " ");
            }
            else if (evnt.button.button == SDL_BUTTON_RIGHT)
            {
                Debug("ADlay");
            }
            break;
    }
}