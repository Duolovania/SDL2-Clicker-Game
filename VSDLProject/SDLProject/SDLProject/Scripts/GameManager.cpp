#include "Headers/gamemanager.h"

void GameManager::Begin()
{
	Debug("gamemanager ");
	score = 0;
	while (Game::gameState != GameState::EXIT)
	{
		GameManager::Forever();
	}
}

void GameManager::PlayerAction()
{
	score++;
}

void GameManager::Forever()
{
	Debug("riddle me this batman");
}