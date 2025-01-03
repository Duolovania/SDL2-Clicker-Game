#include "image.h"

Image::Image(std::string path, SDL_Renderer* render) 
	: transform(Vector2(), Vector2())
{
	if (path != "")
	{
		std::string newPath = "Assets/Textures/" + path;
		std::string debugPath = newPath;

		renderer = render;
		
		img = IMG_LoadTexture(renderer, newPath.c_str());
		SDL_QueryTexture(img, NULL, NULL, &rect.w, &rect.h);

		std::shared_ptr<Image> tempImg = std::make_unique<Image>();

		tempImg->transform = this->transform;
		tempImg->rect = this->rect;
		tempImg->renderer = this->renderer;
		tempImg->img = this->img;

		std::shared_ptr<GameObject> tempgObj = tempImg;

		GameObject::gObjs.push_back(tempgObj);
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

void Image::Load(std::string path)
{
	std::string newPath = "Assets/Textures/" + path;

	if (img != nullptr) SDL_DestroyTexture(img);
	img = IMG_LoadTexture(renderer, newPath.c_str());
}