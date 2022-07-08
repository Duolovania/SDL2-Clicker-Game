#pragma once
#include "SDl_image.h"

class Image
{
	public:
		Image(const char* path, SDL_Renderer* render);
		void SetTransform(int x, int y, int w, int h);
		void QueryText();
		void Draw();

		SDL_Texture* img;
		SDL_Surface* surf = IMG_Load("DevAssets/Textures/colonel.png");
		SDL_Rect rect;
		SDL_Renderer* renderer;
};