#include "Headers/gamemanager.h"

void GameManager::Begin()
{
	Debug("gamemanager running ");
	score = 0;
}

void GameManager::PlayerAction()
{
	score++;
}