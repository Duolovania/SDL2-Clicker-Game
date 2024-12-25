#pragma once
#include "game.h"

class GameManager : Game
{
	public:
		int score;
		void PlayerAction();
		void Upgrade();

		int upgradeCost = 10;
		int perClick = 1;

		GameManager() { Begin(); }

	protected:
		void Begin();
};