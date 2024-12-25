#define _CRTDBG_MAP_ALLOC

#include "game.h"
#include "text.h"
#include "image.h"
#include "audio.h"
#include "gamemanager.h"
#include <cmath>
#include "crtdbg.h"

GameManager gameManager;
SDL_Surface* iconSurf = IMG_Load("Assets/Textures/colonel.png");
Mix_Music* bgm;
Mix_Chunk* noot;
Mix_Chunk* fLick;
Mix_Chunk* tick;

SDL_Color textCol = { 255, 255, 255 };

Text wtitle;
Text prompt;
Text wKey;

Image wWing;
Image wSanders;
Image wLogo;
Image wBucket;

Image oliver;

Vector2 mousePos;

bool gameRunning = false;
const char* scorePtr;

Vector2 wingUpScale;

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
    Debug("Entry Point Reached. Running Version 1.0");
    while (gameState != GameState::EXIT)
    {
        Forever();
    }

    Mix_FreeMusic(bgm);
    Mix_FreeChunk(fLick);
    Mix_FreeChunk(noot);

    //SDL_DestroyTexture(wWing.img);
    //SDL_DestroyTexture(wSanders.img);
    //SDL_DestroyTexture(prompt.msg);
    //SDL_DestroyTexture(wtitle.msg);
    //SDL_DestroyTexture(wKey.msg);
    //SDL_DestroyTexture(oliver.img);

    for (auto gObj : GameObject::gObjs)
    {
        gObj->OnGameEnd();
        //Game::Debug("pointuh problemo");
    }

    SDL_DestroyWindow(window);
    //TTF_CloseFont(wtitle.font);
    //TTF_CloseFont(prompt.font);
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

    wSanders = Image("buff.png", renderer);
    wSanders.SetTransform(screenWidth - 1400, screenHeight - 400, w * 6, h * 3);

    oliver = Image("oliv.JPG", renderer);
    oliver.SetTransform(screenWidth * 2, screenHeight, w * 6, h * 3);

    wKey = Text("Assets/Fonts/lemonMilk.otf", 60, textCol, renderer);
    wKey.ModifyText("Press any Key to Begin.");
    wKey.SetTransform((screenWidth / 2 - 400), (screenHeight / 2 - 150), 100, 100);

    wtitle = Text("Assets/Fonts/OlivettiNeue.otf", 30, textCol, renderer);
    wtitle.ModifyText("0");
    wtitle.SetTransform((screenWidth / 2 - 480), (screenHeight / 2 - 300), 100, 100);

    prompt = Text("Assets/Fonts/font.ttf", 50, textCol, renderer);
    prompt.ModifyText("Click the Chicken");
    prompt.SetTransform(screenWidth / 2 - 480, screenHeight / 2 + 230, 100, 100);

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
    
    if (gameRunning)
    {
        // Refreshing textures.
        wSanders.Draw();
        oliver.Draw();
        wWing.Draw();
        wtitle.Draw();
        prompt.Draw();
        wBucket.Draw();

        // Sine wave movement.
        wWing.transform.position.y = ((sin((time) * 10)) * 10) + 150;
        prompt.transform.position.x = ((cos((time) * 20)) * 2) + 25;

        wSanders.SetAlpha(((sin((time) * 20)) * 10) + 150);

        //if (evnt.button.button == SDL_BUTTON_LEFT && distanceFromCursor() < 150) 
        SDL_GetMouseState(&mousePos.x, &mousePos.y);

        if (wWing.transform.DistanceTo(mousePos) < 150)
        {
            wWing.transform.scale = wingUpScale;
        }

        std::string strObj(std::to_string(gameManager.score));
        scorePtr = &strObj[0];

        wtitle.ModifyText(scorePtr);
        wtitle.transform = Transform(Vector2((screenWidth / 2 - 480), (screenHeight / 2 - 300)), Vector2::Uniform(100));

        SDL_SetRenderDrawColor(renderer, 204, 41, 54, 255);

        if (wBucket.transform.DistanceTo(mousePos) < 40)
        {
            if (gameManager.score >= gameManager.upgradeCost) wBucket.Load("Assets/Textures/a.png");
            else wBucket.Load("Assets/Textures/na.png");
        }
        else
        {
            wBucket.Load("Assets/Textures/i.png");
        }

        if (!Mix_PlayingMusic())
        {
            Mix_PlayChannel(-1, fLick, 0);
            Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
            Mix_PlayMusic(bgm, -1);
        }
    }
    else
    {
        wLogo.Draw();
        wKey.Draw();

        wKey.transform.position = Vector2((((sin((time) * 10)) * 2) + 400), ((cos((time) * 10)) * 2) + 150);
        SDL_SetRenderDrawColor(renderer, 26, 24, 27, 255);
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