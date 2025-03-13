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
    this->targetNames = { "Topaz", "Sparkle", "Jingliu", "Aventurine", "Blade", "JingYuan", "Kafka", "March7th", "Rappa", "RuanMei" };

    this->scoreboard = dynamic_cast<Scoreboard*>(GameObjectManager::getInstance()->findObjectByName("scoreboard"));
    this->target = dynamic_cast<Target*>(GameObjectManager::getInstance()->findObjectByName("target"));
    this->sd = dynamic_cast<SearchDisplay*>(GameObjectManager::getInstance()->findObjectByName("SearchDisplay"));
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

void GameplayManager::setRandomTarget()
{
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<int> dist(0, 9);

    this->setTarget(this->targetNames[dist(engine)]);
}

std::string GameplayManager::getTarget()
{
    return this->curTarget;
}

void GameplayManager::startRound()
{
    this->setRandomTarget();

    // We probably want a randomizer for which the game modes would be, and a randomizer for the params too, and the entity count
    this->sd->setEntityCount(50);
    this->sd->arrangeGrid(10, 10.0f);
    //this->sd->scatterRandom(50.0f);
}

void GameplayManager::winRound()
{
    this->sd->resetExceptTarget();

    // Wait for 2 seconds

    this->startRound();
}
