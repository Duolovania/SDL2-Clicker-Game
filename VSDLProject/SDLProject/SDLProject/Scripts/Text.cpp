#include "Headers/text.h"

Text::Text(const char* path, int size, SDL_Color col, SDL_Renderer* render)
{
	renderer = render;
	color = col;

	font = TTF_OpenFont(path, size);
	ModifyText("New Text");
}

Text::~Text() {}

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

void Text::ModifyText(const char* newText)
{
	surf = TTF_RenderText_Solid(font, newText, color);
	if (msg != nullptr) SDL_DestroyTexture(msg);
	msg = SDL_CreateTextureFromSurface(renderer, surf);

	SDL_FreeSurface(surf);
}

void Text::MoveX(float steps)
{
	rect.x += steps;
}

void Text::MoveY(float steps)
{
	rect.y += -steps;
}

void Text::SetY(float newPos)
{
	rect.y = newPos;
}

void Text::SetX(float newPos)
{
	rect.x = newPos;
}