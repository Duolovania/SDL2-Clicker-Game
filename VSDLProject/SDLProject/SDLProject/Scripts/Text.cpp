#include "Headers/text.h"

Text::Text(const char* text, const char* path, int size, SDL_Color col, SDL_Renderer* render)
{
	renderer = render;
	color = col;

	font = TTF_OpenFont(path, size);
	surf = TTF_RenderText_Solid(font, text, col);
	msg = SDL_CreateTextureFromSurface(renderer, surf);
};

void Text::SetTransform(int x, int y, int w, int h)
{
	rect.x = x;
	rect.y = y;

	rect.w = w;
	rect.h = h;
}

void Text::QueryText()
{
	SDL_QueryTexture(msg, NULL, NULL, &rect.w, &rect.h);
}

void Text::Draw()
{
	SDL_RenderCopy(renderer, msg, NULL, &rect);
}