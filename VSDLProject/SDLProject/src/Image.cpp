#include "image.h"

Image::Image(std::string path, SDL_Renderer* render) : transform(Vector2(), Vector2())
{
	if (path != "")
	{
		std::string combinedPath = "DevAssets/Textures/" + path;

		const char* newPath = combinedPath.c_str();
		std::string debugPath = newPath;

		std::string newLog = (std::string)"->Image Object: " + debugPath + " Successfully Loaded.";
		Game::Debug(newLog);

		renderer = render;
		
		img = IMG_LoadTexture(renderer, newPath);
		SDL_QueryTexture(img, NULL, NULL, &rect.w, &rect.h);
		GameObject::gObjs.push_back(this);
	}
}

Image::~Image() {}

void Image::SetTransform(int x, int y, int w, int h)
{
	transform.position = Vector2(x / 2 - 150, y / 2 - 100);
	transform.scale = Vector2(w / 3.5, h / 2);
}

void Image::Draw()
{
	rect.x = transform.position.x;
	rect.y = transform.position.y;

	rect.w = transform.scale.x;
	rect.h = transform.scale.y;

	SDL_RenderCopy(this->renderer, img, NULL, &this->rect);
}

void Image::SetAlpha(int newAlpha)
{
	SDL_SetTextureAlphaMod(img, newAlpha);
}

void Image::Load(const char* path)
{
	if (img != nullptr) SDL_DestroyTexture(img);
	img = IMG_LoadTexture(renderer, path);
}

//void Image::OnGameEnd()
//{
//	if (img != nullptr) SDL_DestroyTexture(img);
//}