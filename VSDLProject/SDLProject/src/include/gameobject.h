#pragma once
#include "game.h"

class GameObject
{
	public:
		virtual void SetTransform(int x, int y, int w, int h) = 0;
		virtual void Draw() = 0;
		virtual void OnGameEnd() = 0;

		GameObject();	
		static std::vector<std::shared_ptr<GameObject>> gObjs;
};