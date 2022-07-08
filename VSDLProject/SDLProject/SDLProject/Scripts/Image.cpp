#include "Headers/image.h"

Image::Image(const char* path, SDL_Renderer* render)
{
	renderer = render;
	surf = IMG_Load(path);
	img = IMG_LoadTexture(renderer, "DevAssets/Textures/wickedwing.png");
}

void Image::SetTransform(int x, int y, int w, int h)
{
	rect.x = x / 2 - 150; 
	rect.y = y / 2 - 100; 
	rect.w = w / 3; 
	rect.h = h / 2;
}

void Image::Draw()
{
	SDL_RenderCopy(this->renderer, img, NULL, &this->rect);
}

void Image::QueryText()
{
	SDL_QueryTexture(img, NULL, NULL, &rect.w, &rect.h);
}