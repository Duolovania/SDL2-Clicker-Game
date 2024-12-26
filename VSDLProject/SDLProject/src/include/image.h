#pragma once
#include "SDL_image.h"
#include "gameobject.h"

class Image : public GameObject
{
	public:
		Image(std::string path = "", SDL_Renderer* render = nullptr);
		~Image();

		Transform transform;

		void SetTransform(int x, int y, int w, int h);
		void Draw();

		void SetAlpha(int newAlpha);
		void Load(const char* path);

		void OnGameEnd()
		{
			if (img != nullptr) SDL_DestroyTexture(img);
		}

	private:
		SDL_Texture* img;
		SDL_Rect rect;
		SDL_Renderer* renderer;
};