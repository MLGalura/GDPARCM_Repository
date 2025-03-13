#include "GameplayManager.h"
#include <iostream>

GameplayManager* GameplayManager::sharedInstance = NULL;

GameplayManager* GameplayManager::getInstance()
{
    if (sharedInstance == NULL) {
        //initialize
        sharedInstance = new GameplayManager();
    }

    return sharedInstance;
}

GameplayManager::GameplayManager() {}

void GameplayManager::initialize()
{
}

void GameplayManager::update(sf::Time elapsedTime)
{
}

void GameplayManager::setScore(int value)
{
}

void GameplayManager::setTarget(std::string name)
{
}
