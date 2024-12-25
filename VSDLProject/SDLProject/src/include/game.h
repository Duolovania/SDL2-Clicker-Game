#pragma once

#include <iostream>

//#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <string>
#include "windows.h"
#include "transform.h"
#include <vector>

enum class GameState { PLAY, EXIT };

class Game
{
    public:
        Game();
        ~Game();
        GameState gameState;
        SDL_Event evnt;
       
        void Run(); // Runs program.

        static void Debug(std::string log)
        { 
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            std::cout << "\n" << log;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        }

    private:
        void Init(const char* title, int x, int y, int w, int h, Uint32 flags); // Initializes window.
        virtual void Forever(); // Game loop

        void HandleEvents();
        void ClickEvent();
        void KeyEvent();

        float time = 0;
        float delta = 0;
        
        SDL_Window* window;
        SDL_Renderer* renderer;
        
        int screenHeight, screenWidth;
};