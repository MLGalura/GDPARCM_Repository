#pragma once
#include <string>
#include "Target.h"
#include "ClickEntity.h"
#include "Scoreboard.h"
#include "SearchDisplay.h"
#include "PointHover.h"

enum GameMode { GRID, SCATTER };

class GameplayManager
{
public:
    static GameplayManager* getInstance();

    void initialize();
    void update(sf::Time elapsedTime);

    void setScore(int value);
    int getScore();
    void showPointGain(float posX, float posY, std::string points, sf::Color color);

    void setTarget(std::string name);
    void setRandomTarget();
    std::string getTarget();

    void startRound();
    void winRound();
    void endGame();

    void setupGridMode();
    void setupScatterMode();

private:
    GameMode currentMode;
    bool isWaitingForRound = false;
    float roundWaitTimer = 0.0f;

    std::vector<std::string> targetNames;
    int curScore;
    std::string curTarget;

    Scoreboard* scoreboard;
    Target* target;
    SearchDisplay* sd;
    PointHover* pointhover;

    bool soundFlag = true;

    GameplayManager();
    GameplayManager(GameplayManager const&) {};             // copy constructor is private
    GameplayManager& operator=(GameplayManager const&) {};  // assignment operator is private
    static GameplayManager* sharedInstance;
};