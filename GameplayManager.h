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
    int getScore();
    void setTarget(std::string name);
    std::string getTarget();

private:
    int curScore;
    std::string curTarget;

    Scoreboard* scoreboard;
    Target* target;

    GameplayManager();
    GameplayManager(GameplayManager const&) {};             // copy constructor is private
    GameplayManager& operator=(GameplayManager const&) {};  // assignment operator is private
    static GameplayManager* sharedInstance;
};