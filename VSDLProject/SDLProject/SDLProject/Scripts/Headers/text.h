#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

class Text
{
	public:
		Text(const char* path, int size, SDL_Color col, SDL_Renderer* render);
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