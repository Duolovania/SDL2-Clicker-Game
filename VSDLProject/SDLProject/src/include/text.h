#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "gameobject.h"

class Text : public GameObject
{
	public:
		Text(const char* path = nullptr, int size = 0, SDL_Color col = {255, 255, 255}, SDL_Renderer* render = nullptr);
		~Text();

		Transform transform;

		//void SetTransform(int x, int y, int w, int h);

		void SetTransform(int x, int y, int w, int h)
		{
			transform.position = Vector2(x, y);
			transform.scale = Vector2(w, h);
		}

		void Draw()
		{
			rect.x = transform.position.x;
			rect.y = transform.position.y;

			rect.w = transform.scale.x;
			rect.h = transform.scale.y;

			SDL_RenderCopy(renderer, msg, NULL, &rect);


		}

		void OnGameEnd()
		{
			if (msg != nullptr) SDL_DestroyTexture(msg);
			TTF_CloseFont(font);
		}

		//void Draw();
		//void OnGameEnd();

		void SetAlpha(int newAlpha);
		void ModifyText(const char* newText);

	private:
		TTF_Font* font;
		SDL_Color color;

		SDL_Surface* surf;
		SDL_Texture* msg = nullptr;

		SDL_Rect rect;
		SDL_Renderer* renderer;
};