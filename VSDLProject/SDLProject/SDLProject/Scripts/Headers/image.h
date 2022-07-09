#pragma once
#include "SDl_image.h"

class Image
{
	public:
		Image(const char* path, SDL_Renderer* render);
		~Image();

		void SetTransform(int x, int y, int w, int h);
		void QueryText();
		void Draw();

		void MoveX(float steps);
		void MoveY(float steps);

		void SetY(float newPos);
		void SetX(float newPos);

		void Scale(float size);

		SDL_Texture* img;
		SDL_Surface* surf = IMG_Load("DevAssets/Textures/colonel.png");
		SDL_Rect rect;
		SDL_Renderer* renderer;

		float scaleX;
		float scaleY;
};