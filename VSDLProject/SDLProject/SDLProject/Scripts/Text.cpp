#include "Headers/text.h"

Text::Text(const char* path, int size, SDL_Color col, SDL_Renderer* render) : transform(Vector2(), Vector2())
{
	Game::Debug("->Text Object Successfully Instanced.");
	renderer = render;
	color = col;

	font = TTF_OpenFont(path, size);
	ModifyText("New Text");

	SDL_QueryTexture(msg, NULL, NULL, &rect.w, &rect.h);
	GameObject::gObjs.push_back(this);
}

Text::~Text() {}

//void Text::SetTransform(int x, int y, int w, int h)
//{
//	transform.position = Vector2(x, y);
//	transform.scale = Vector2(w, h);
//}

//void Text::Draw()
//{
//	rect.x = transform.position.x;
//	rect.y = transform.position.y;
//
//	rect.w = transform.scale.x;
//	rect.h = transform.scale.y;
//
//	SDL_RenderCopy(renderer, msg, NULL, &rect);
//}

void Text::ModifyText(const char* newText)
{
	surf = TTF_RenderText_Solid(font, newText, color);
	if (msg != nullptr) SDL_DestroyTexture(msg);
	msg = SDL_CreateTextureFromSurface(renderer, surf);

	SDL_FreeSurface(surf);
}

//void Text::OnGameEnd()
//{
//	if (msg != nullptr) SDL_DestroyTexture(msg);
//	TTF_CloseFont(font);
//}