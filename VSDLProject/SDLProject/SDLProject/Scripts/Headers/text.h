#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

class Text
{
	public:
		Text(const char* text, const char* path, int size, SDL_Color col, SDL_Renderer* render);
		void SetTransform(int x, int y, int w, int h);
		void QueryText();
		void Draw();

		TTF_Font* font;
		SDL_Color color;

		SDL_Surface* surf;
		SDL_Texture* msg;

		SDL_Rect rect;
		SDL_Renderer* renderer;

	private:
		
};