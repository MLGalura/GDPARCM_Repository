#pragma once
#include <string>
#include "Target.h"
#include "ClickEntity.h"
#include "Scoreboard.h"

class GameplayManager
{
public:
    static GameplayManager* getInstance();

    void initialize();
    void update(sf::Time elapsedTime);

    void setScore(int value);
    void setTarget(std::string name);

private:
    int curScore;
    std::string curTarget;

    GameplayManager();
    GameplayManager(GameplayManager const&) {};             // copy constructor is private
    GameplayManager& operator=(GameplayManager const&) {};  // assignment operator is private
    static GameplayManager* sharedInstance;
};