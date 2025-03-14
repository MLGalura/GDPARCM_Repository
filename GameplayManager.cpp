#include "GameplayManager.h"
#include "GameObjectManager.h"
#include "SoundManager.h"
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
    if (isWaitingForRound) {
        roundWaitTimer += elapsedTime.asSeconds();

        if (roundWaitTimer >= 1.0f && this->soundFlag) {
            SoundManager::getInstance()->playSound("Snare");
            this->soundFlag = false;
        }

        if (roundWaitTimer >= 2.4f) {
            isWaitingForRound = false;
            this->soundFlag = true;

            startRound();
        }
    }
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

    // Randomize game mode
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> modeDist(0, 1);
    currentMode = static_cast<GameMode>(modeDist(gen));

    if (this->currentMode == GRID) {
        std::uniform_int_distribution<> countDist(15, 45);
        int entityCount = countDist(gen);

        this->sd->setEntityCount(entityCount);

        this->setupGridMode();
    }

    else 
        this->setupScatterMode();

}

void GameplayManager::winRound()
{
    this->isWaitingForRound = true;
    this->roundWaitTimer = 0.0f;
    this->sd->resetExceptTarget();
}

void GameplayManager::endGame()
{
    this->sd->end();
    this->scoreboard->callEnd();
    this->target->callEnd();
}

void GameplayManager::setupGridMode()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // Random columns x, y respectively
    std::uniform_int_distribution<> colDist(5, 12);
    int columns = colDist(gen);

    // Random padding x, y respectively
    std::uniform_real_distribution<float> padDist(20.0f, 40.0f);
    float padding = padDist(gen);

    this->sd->arrangeGrid(columns, padding);
}

void GameplayManager::setupScatterMode()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // Random padding x, y respectively
    std::uniform_real_distribution<float> padDist(50.0f, 100.0f);
    float padding = padDist(gen);

    this->sd->scatterRandom(padding);
}
