#pragma once
#include "game.h"

class GameManager : Game
{
	public:
		int score;
		void PlayerAction();

		GameManager() 
		{
			Begin();
		}

	protected:
		void Begin();
};