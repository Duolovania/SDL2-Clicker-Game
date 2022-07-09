#define _CRTDBG_MAP_ALLOC

#include "Headers/game.h"
#include "Headers/text.h"
#include "Headers/image.h"
#include "Headers/audio.h"
#include "Headers/gamemanager.h"
#include <cmath>
#include "crtdbg.h"
#include <memory>

GameManager gameManager;
SDL_Surface* iconSurf = IMG_Load("DevAssets/Textures/colonel.png");
Mix_Music* bgm;
Mix_Chunk* noot;
Mix_Chunk* fLick;

SDL_Color textCol = { 255, 255, 255 };

std::unique_ptr<Text> wtitle;
std::unique_ptr<Text> prompt;
std::unique_ptr<Image> wWing;

int mouseY = 0;
int mouseX = 0;

const char* scorePtr;

Game::Game()
{
    window = nullptr;
    renderer = nullptr;
    screenHeight = 600;
    screenWidth = 1024;
    gameState = GameState::PLAY;
}

Game::~Game() {}

// Called at launch.
void Game::Run()
{
    Init("Please stop ordering Jumbo Bkts.", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    Debug("Entry Point Reached");
    while (gameState != GameState::EXIT) Forever();

    Mix_FreeMusic(bgm);
    Mix_FreeChunk(fLick);
    Mix_FreeChunk(noot);
    SDL_DestroyTexture(wWing->img);
    SDL_DestroyTexture(prompt->msg);
    SDL_DestroyTexture(wtitle->msg);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
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
    
    wtitle = std::make_unique<Text>(Text("DevAssets/Fonts/OlivettiNeue.otf", 30, textCol, renderer));
    wtitle->ModifyText("0");
    wtitle->SetTransform((screenWidth / 2 - 480), (screenHeight / 2 - 300), 100, 100);
    wtitle->QueryText();

    prompt = std::make_unique<Text>(Text("DevAssets/Fonts/font.ttf", 50, textCol, renderer));
    prompt->ModifyText("Click the Chicken");
    prompt->SetTransform(screenWidth / 2 - 480, screenHeight / 2 + 230, 100, 100);
    prompt->QueryText();


    wWing = std::make_unique<Image>(Image("DevAssets/Textures/wickedwing.png", renderer));
    wWing->QueryText();
    wWing->SetTransform(screenWidth, screenHeight, w, h);

    bgm = Mix_LoadMUS("DevAssets/SFX/ov.mp3");
    noot = Mix_LoadWAV("DevAssets/SFX/noto.wav");
    fLick = Mix_LoadWAV("DevAssets/SFX/kfc.wav");

    Mix_PlayChannel(-1, fLick, 0);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    if (!Mix_PlayingMusic()) Mix_PlayMusic(bgm, -1);

    SDL_FreeSurface(iconSurf);
    
    SDL_SetRenderDrawColor(renderer, 224, 57, 45, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

// Game loop.
void Game::Forever()
{
    HandleEvents();
    
    // clear the screen
    SDL_RenderClear(renderer);
    
    // Refreshing textures.
    wWing->Draw(); 
    wtitle->Draw();
    prompt->Draw();
    
    // Sine wave movement.
    wWing->SetY(((sin((time) * 10)) * 10) + 150); 
    if (evnt.button.button == SDL_BUTTON_LEFT) wWing->Scale(((sin((time) * 10000)) * 10));
    prompt->SetX(((cos((time) * 20)) * 2) + 25);

    std::string strObj(std::to_string(gameManager.score));
    scorePtr = &strObj[0];

    wtitle->ModifyText(scorePtr);
    wtitle->SetTransform((screenWidth / 2 - 480), (screenHeight / 2 - 300), 100, 100);

    SDL_RenderPresent(renderer);
    _CrtDumpMemoryLeaks();
    
    delta += 1;
    time += 0.01;
}

// Calculates distance from mouse cursor
double distanceFromCursor()
{
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
    }
}

// Defines Keyboard events
void Game::KeyEvent()
{
    switch (evnt.key.keysym.sym)
    {
        default:
            break;
    }
}

// Defines Mouse events
void Game::ClickEvent()
{
    switch (evnt.button.button)
    {
        case (SDL_BUTTON_LEFT):
            if (distanceFromCursor() < 150)
            {
                gameManager.PlayerAction();
                Mix_PlayChannel(-1, noot, 0);
            }
            break;
    }
}