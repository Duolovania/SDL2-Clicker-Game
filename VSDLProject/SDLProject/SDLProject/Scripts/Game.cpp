#include "Headers/game.h"
#include "Headers/gamemanager.h"
#include <cmath>

SDL_Texture* img;
SDL_Surface* iconSurf = IMG_Load("DevAssets/Textures/colonel.png");
SDL_Rect texr;

GameManager gameManager;

TTF_Font* scoreFont;
SDL_Color fontCol = { 255, 255, 255 };
SDL_Surface* textSurf;
SDL_Texture* textMsg;
SDL_Rect textRect;

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
    while (gameState != GameState::EXIT) Forever();
}

// Init window and renderer.
void Game::Init(const char* title, int x, int y, int w, int h, Uint32 flags)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    if (TTF_Init() < 0) Debug("Error");
    window = SDL_CreateWindow(title, x, y, w, h, flags);
    
    SDL_SetWindowIcon(window, iconSurf);
    renderer = SDL_CreateRenderer(window, -1, 0);

    scoreFont = TTF_OpenFont("DevAssets/Fonts/OlivettiNeue.otf", 50);
    textSurf = TTF_RenderText_Solid(scoreFont, "The", fontCol);
    textMsg = SDL_CreateTextureFromSurface(renderer, textSurf);
    
    textRect.x = screenWidth / 2 - 200;
    textRect.y = screenHeight / 2 - 200;
    
    textRect.w = 1500;
    textRect.h = 1500;

    SDL_QueryTexture(textMsg, NULL, NULL, &textRect.w, &textRect.h);

    SDL_SetRenderDrawColor(renderer, 224, 57, 45, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    img = IMG_LoadTexture(renderer, "DevAssets/Textures/wickedwing.png");

    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    texr.x = screenWidth / 2 - 150; texr.y = screenHeight / 2 - 100; texr.w = w / 2; texr.h = h / 2;
}

// Game loop.
void Game::Forever()
{
    HandleEvents();

    // clear the screen
    SDL_RenderClear(renderer);
    // copy the texture to the rendering context
    SDL_RenderCopy(renderer, img, NULL, &texr);
    SDL_RenderCopy(renderer, textMsg, NULL, &textRect);
    // flip the backbuffer
    // this means that everything that we prepared behind the screens is actually shown
    SDL_RenderPresent(renderer);
}

double distanceFromCursor()
{
    int mouseX = 0;
    int mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);

    return sqrt(pow((texr.x + texr.w / 2) - mouseX, 2) + pow((texr.y + texr.h / 2) - mouseY, 2));
}

// Event handler.
void Game::HandleEvents()
{
    SDL_PollEvent(&evnt);

    switch (evnt.type)
    {
        case SDL_QUIT:
            gameState = GameState::EXIT;
            break;
        case SDL_MOUSEBUTTONDOWN:
            ClickEvent();
            break;
    }
}

void Game::ClickEvent()
{
    if (evnt.button.button == SDL_BUTTON_LEFT && distanceFromCursor() < 150)
    {
        gameManager.PlayerAction();
        Debug(std::to_string(gameManager.score) + " ");
    }
    else if (evnt.button.button == SDL_BUTTON_RIGHT)
    {
        Debug("ADlay");
    }
}