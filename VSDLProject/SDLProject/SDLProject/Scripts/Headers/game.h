#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_image.h"
#include <string>

enum class GameState { PLAY, EXIT };

class Game
{
    public:
        Game();
        ~Game();
        GameState gameState;
        SDL_Event evnt;
       
        void Run(); // Runs program.
        static void Debug(std::string log) { std::cout << log; }

    private:
        void Init(const char* title, int x, int y, int w, int h, Uint32 flags); // Initializes window.
        void HandleEvents();
        
        SDL_Window* window;
        SDL_Renderer* renderer;
        
        int screenHeight, screenWidth;

    protected:
        virtual void Forever(); // Game loop
};