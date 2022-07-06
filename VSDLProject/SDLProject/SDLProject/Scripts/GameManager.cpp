#include "Headers/gamemanager.h"

void GameManager::Begin()
{
	Debug("gamemanager ");
	score = 0;
}

void GameManager::PlayerAction()
{
	score++;
}