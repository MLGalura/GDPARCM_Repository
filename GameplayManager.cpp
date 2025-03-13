#include "GameplayManager.h"
#include "GameObjectManager.h"
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
    this->curTarget = "Sparkle";

    this->scoreboard = dynamic_cast<Scoreboard*>(GameObjectManager::getInstance()->findObjectByName("scoreboard"));
    this->target = dynamic_cast<Target*>(GameObjectManager::getInstance()->findObjectByName("target"));
}

void GameplayManager::update(sf::Time elapsedTime)
{
}

void GameplayManager::setScore(int value)
{
    this->curScore = value;
    this->scoreboard->setScore(this->curScore);
}

int GameplayManager::getScore()
{
    return this->curScore;
}

void GameplayManager::setTarget(std::string name)
{
    this->curTarget = name;
    this->target->setTarget(this->curTarget);
}

std::string GameplayManager::getTarget()
{
    return this->curTarget;
}
