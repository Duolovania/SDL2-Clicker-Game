#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "game.h"

class Text
{
	public:
		Text(const char* path = nullptr, int size = 0, SDL_Color col = {255, 255, 255}, SDL_Renderer* render = nullptr);
		~Text();

		void SetTransform(int x, int y, int w, int h);
		void QueryText();
		void Draw();

		void MoveX(float steps);
		void MoveY(float steps);
		
		void SetY(float newPos);
		void SetX(float newPos);
		void ModifyText(const char* newText);

		TTF_Font* font;
		SDL_Color color;

		SDL_Surface* surf;
		SDL_Texture* msg = nullptr;

		SDL_Rect rect;
		SDL_Renderer* renderer;
};