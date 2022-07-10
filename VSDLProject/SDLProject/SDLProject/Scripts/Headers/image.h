#pragma once
#include "SDl_image.h"
#include "game.h"
#include <vector>

class Image
{
	public:
		Image(const char* path = nullptr, SDL_Renderer* render = nullptr);
		~Image();

		void SetTransform(int x, int y, int w, int h);
		void QueryText();
		void Draw();

		void MoveX(float steps);
		void MoveY(float steps);

		void SetY(float newPos);
		void SetX(float newPos);

		void Scale(float size);
		void Load(const char* path);

		SDL_Texture* img;
		SDL_Rect rect;
		SDL_Renderer* renderer;

		float scaleX;
		float scaleY;
};