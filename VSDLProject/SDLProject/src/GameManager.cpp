#include "gamemanager.h"

void GameManager::Begin()
{
	Debug("GameManager in Operation.");
	score = 0;
}

void GameManager::PlayerAction()
{
	score += perClick;
}

void GameManager::Upgrade()
{
	if (score >= upgradeCost)
	{
		score -= upgradeCost;
		perClick++;
		upgradeCost += round(perClick * 1.5);
	}
}