#include "Headers/image.h"

Image::Image(const char* path, SDL_Renderer* render)
{
	Game::Debug("->Image Object Successfully Instanced.");
	renderer = render;
	if (path != nullptr) img = IMG_LoadTexture(renderer, path);
}

Image::~Image() {}

void Image::SetTransform(int x, int y, int w, int h)
{
	rect.x = x / 2 - 150; 
	rect.y = y / 2 - 100;

	scaleX = w / 3.5;
	scaleY = h / 2;

	rect.w = scaleX; 
	rect.h = scaleY;
}

void Image::Draw()
{
	SDL_RenderCopy(this->renderer, img, NULL, &this->rect);
}

void Image::QueryText()
{
	SDL_QueryTexture(img, NULL, NULL, &rect.w, &rect.h);
}

void Image::Load(const char* path)
{
	if (img != nullptr) SDL_DestroyTexture(img);
	img = IMG_LoadTexture(renderer, path);
}

void Image::MoveX(float steps)
{
	rect.x += steps;
}

void Image::MoveY(float steps)
{
	rect.y += -steps;
}

void Image::SetY(float newPos)
{
	rect.y = newPos;
}

void Image::SetX(float newPos)
{
	rect.x = newPos;
}

void Image::Scale(float size)
{
	rect.w += size;
	rect.h += size;
}