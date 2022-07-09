#include "Headers/game.h"
#include "Headers/text.h"
#include "Headers/image.h"
#include "Headers/audio.h"
#include "Headers/gamemanager.h"
#include <cmath>

GameManager gameManager;
SDL_Surface* iconSurf = IMG_Load("DevAssets/Textures/colonel.png");
Mix_Music* bgm;
Mix_Chunk* noot;
float deltaTime = 0;

SDL_Color textCol = { 255, 255, 255 };
SDL_Texture* textMsg;
SDL_Rect textRect;

Text* wtitle;
Image* wWing;

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
    while (gameState != GameState::EXIT) Forever(deltaTime);
}

// Init window and renderer.
void Game::Init(const char* title, int x, int y, int w, int h, Uint32 flags)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    if (TTF_Init() < 0) Debug("\nError Text");
    if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT, 2, 2048) < 0) Debug("\nError Music");
    
    window = SDL_CreateWindow(title, x, y, w, h, flags);
    renderer = SDL_CreateRenderer(window, -1, 0);
    
    SDL_SetWindowIcon(window, iconSurf);
    
    wtitle = new Text("Ranuts balls are smaller than his head", "DevAssets/Fonts/OlivettiNeue.otf", 30, textCol, renderer);
    wtitle->SetTransform((screenWidth / 2 - 200), (screenHeight / 2 - 100), 1500, 1500);
    wtitle->QueryText();

    wWing = new Image("DevAssets/Textures/wickedwing.png", renderer);
    wWing->QueryText();
    wWing->SetTransform(screenWidth, screenHeight, w, h);

    bgm = Mix_LoadMUS("DevAssets/SFX/ov.mp3");
    //noot = Mix_LoadWAV("DevAssets/SFX/noto.wav");
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    if (!Mix_PlayingMusic()) Mix_PlayMusic(bgm, -1);
    

    SDL_SetRenderDrawColor(renderer, 224, 57, 45, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

// Game loop.
void Game::Forever(float delta)
{
    HandleEvents();

    // clear the screen
    SDL_RenderClear(renderer);
    
    wWing->Draw();
    wtitle->Draw();
    wWing->SetY(2 * cos(delta));
    SDL_RenderPresent(renderer);
    delta += 0.1;
}

double distanceFromCursor()
{
    int mouseX = 0;
    int mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);

    return sqrt(pow((wWing->rect.x + wWing->rect.w / 2) - mouseX, 2) + pow((wWing->rect.y + wWing->rect.h / 2) - mouseY, 2));
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
        case SDL_KEYDOWN:
            KeyEvent();
            break;
        case SDLK_w:
            wWing->MoveY(1);
            break;
        case SDLK_d:
            wWing->MoveX(1);
        case SDLK_s:
            wWing->MoveY(-1);
            break;
        case SDLK_a:
            wWing->MoveX(-1);
    }
}

void Game::KeyEvent()
{
    if (evnt.button.button == SDLK_a)
    {
        wWing->MoveX(-1);
    }
}

void Game::ClickEvent()
{
    if (evnt.button.button == SDL_BUTTON_LEFT && distanceFromCursor() < 150)
    {
        gameManager.PlayerAction();
        //Mix_PlayChannel(-1, noot, 0);
        wWing->MoveX(1);
        wWing->MoveY(1);
        Debug(std::to_string(gameManager.score) + " ");
    }
    else if (evnt.button.button == SDL_BUTTON_RIGHT)
    {
        Debug("ADlay");
    }
}