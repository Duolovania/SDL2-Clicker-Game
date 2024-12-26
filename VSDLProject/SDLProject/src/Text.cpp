#include "text.h"

Text::Text(std::string path, int size, SDL_Color col, SDL_Renderer* render) 
	: transform(Vector2(), Vector2())
{
	Game::Debug("->Text Object Successfully Instanced.");
	renderer = render;
	color = col;

	std::string newPath = "Assets/Fonts/" + path;

	font = TTF_OpenFont(newPath.c_str(), size);
	ModifyText("New Text");

	SDL_QueryTexture(msg, NULL, NULL, &rect.w, &rect.h);

	//std::shared_ptr<Text> tempText = std::make_unique<Text>();

	/*tempText->transform = this->transform;
	tempText->rect = this->rect;
	tempText->renderer = this->renderer;
	tempText->font = this->font;
	tempText->color = this->color;
	tempText->msg = this->msg;

	std::shared_ptr<GameObject> tempgObj = tempText;

	GameObject::gObjs.push_back(tempgObj);*/
}

Text::~Text() {}

void Text::ModifyText(const char* newText)
{
	surf = TTF_RenderText_Solid(font, newText, color);
	if (msg != nullptr) SDL_DestroyTexture(msg);
	msg = SDL_CreateTextureFromSurface(renderer, surf);

	SDL_FreeSurface(surf);
}