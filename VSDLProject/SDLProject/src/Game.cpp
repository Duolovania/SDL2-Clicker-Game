#define _CRTDBG_MAP_ALLOC

#include "game.h"
#include "text.h"
#include "image.h"
#include "audio.h"
#include "gamemanager.h"
#include <cmath>
#include "crtdbg.h"

GameManager gameManager;
SDL_Surface* iconSurf = IMG_Load("Assets/Textures/wickedwing.png");
Mix_Music* bgm;
Mix_Chunk* noot;
Mix_Chunk* fLick;
Mix_Chunk* tick;

SDL_Color textCol = { 255, 255, 255 };

std::shared_ptr<Text> wTitle, prompt, wKey;
Image wWing, wSanders, wLogo, wBucket;

Vector2 mousePos, wingUpScale;

bool gameRunning = false;
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
    Init("Finger Lickin' Good Experience", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    while (gameState != GameState::EXIT)
    {
        Forever();
    }

    Mix_FreeMusic(bgm);
    Mix_FreeChunk(fLick);
    Mix_FreeChunk(noot);

    for (auto gObj : GameObject::gObjs)
    {
        gObj->OnGameEnd();
    }

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
    
    wLogo = Image("DLogo.png", renderer);
    wLogo.SetTransform(screenWidth - 250, screenHeight + 50, w * 2, h / 2);

    wBucket = Image("i.png", renderer);
    wBucket.SetTransform(screenWidth + 1100, screenHeight + 600, w / 3.0, h / 3.5);

    wSanders = Image("colonel-background.png", renderer);
    wSanders.SetTransform(screenWidth - 1400, screenHeight - 400, w * 6, h * 3);

    wKey = std::make_unique<Text>("lemonMilk.otf", 60, textCol, renderer);
    wKey->ModifyText("Press any Key to Begin.");
    wKey->SetTransform((screenWidth / 2 - 200), (screenHeight / 8), screenWidth / 2, screenHeight / 12);

    wTitle = std::make_unique<Text>("OlivettiNeue.otf", 30, textCol, renderer);
    wTitle->ModifyText("0");
    wTitle->SetTransform((screenWidth / 2 - 480), (screenHeight / 2 - 300), 100, 100);

    prompt = std::make_unique<Text>("font.ttf", 50, textCol, renderer);
    prompt->ModifyText("Click the Screen");
    prompt->SetTransform(screenWidth / 2 - 480, screenHeight / 2 + 230, screenWidth / 2, screenHeight / 8);

    wWing = Image("wickedwing.png", renderer);
    wWing.SetTransform(screenWidth, screenHeight, w, h);
    wingUpScale = Vector2::Multiply(wWing.transform.scale, Vector2::Uniform(1.2f));

    bgm = Mix_LoadMUS("Assets/SFX/ov.mp3");
    noot = Mix_LoadWAV("Assets/SFX/Click.wav");
    fLick = Mix_LoadWAV("Assets/SFX/kfc.wav");
    tick = Mix_LoadWAV("Assets/SFX/tick.wav");

    SDL_FreeSurface(iconSurf);
    
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    Mix_PlayChannel(-1, tick, 0);
}

// Game loop.
void Game::Forever()
{
    HandleEvents();
    SDL_Delay(16);

    // clear the screen
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    if (gameRunning)
    {
        SDL_SetRenderDrawColor(renderer, 204, 41, 54, 255);

        // Refreshing textures.
        wSanders.Draw();
        wWing.Draw();
        wTitle->Draw();
        prompt->Draw();
        wBucket.Draw();

        // Sine wave movement.
        wWing.transform.position.y = ((sin((time) * 10)) * 10) + 150;
        prompt->transform.position.x = ((cos((time) * 20)) * 2) + 25;

        wSanders.SetAlpha(((sin((time) * 20)) * 10) + 150);

        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        if (wWing.transform.DistanceTo(mousePos) < 150)
            wWing.transform.scale = wingUpScale;

        wTitle->ModifyText((std::to_string(gameManager.score)));
        wTitle->transform = Transform(Vector2((screenWidth / 2 - 480), (screenHeight / 2 - 300)), Vector2::Uniform(100));

        if (wBucket.transform.DistanceTo(mousePos) < 40)
        {
            if (gameManager.score >= gameManager.upgradeCost) wBucket.Load("a.png");
            else wBucket.Load("na.png");
        }
        else
        {
            wBucket.Load("i.png");
        }

        if (!Mix_PlayingMusic())
        {
            Mix_PlayChannel(-1, fLick, 0);
            Mix_VolumeMusic(MIX_MAX_VOLUME / 10);
            Mix_PlayMusic(bgm, -1);
        }
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 26, 24, 27, 255);

        wLogo.Draw();
        wKey->Draw();

        wKey->transform.position = Vector2((((sin((time) * 10)) * 2) + 275), ((cos((time) * 10)) * 2) + 400);
    }

    SDL_RenderPresent(renderer);
    _CrtDumpMemoryLeaks();
    
    delta += 1;
    time += 0.01;
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
            if (gameRunning) ClickEvent();
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
        case SDLK_SPACE:
            if (gameRunning)
            {
                gameManager.PlayerAction();
                Mix_PlayChannel(-1, noot, 0);
            }
            break;
        default:
            if (!gameRunning) gameRunning = true;
            break;
    }
}

// Defines Mouse events
void Game::ClickEvent()
{
    switch (evnt.button.button)
    {
        case (SDL_BUTTON_LEFT):
            if (wWing.transform.DistanceTo(mousePos) < 150)
            {
                gameManager.PlayerAction();
                Mix_PlayChannel(-1, noot, 0);
            }
            if (wBucket.transform.DistanceTo(mousePos) < 40)
            {
                gameManager.Upgrade();
                Mix_PlayChannel(-1, tick, 0);
            }
            break;
    }
}