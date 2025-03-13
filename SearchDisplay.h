#pragma once
#include "AGameObject.h"
#include "ClickEntity.h"
#include <vector>
#include <random>
#include <algorithm>

class SearchDisplay : public AGameObject {
public:
    SearchDisplay(std::string name);
    ~SearchDisplay();

    void initialize() override;
    void processInput(sf::Event event) override {};
    void update(sf::Time deltaTime) override {};
    void draw(sf::RenderWindow* targetWindow) override;

    void arrangeGrid(int columns, float padding);
    void scatterRandom(int areaPadding);
    void shuffleEntities();
    void reset();
    void resetExceptTarget();

    void setEntityCount(int value);

private:
    std::vector<ClickEntity*> clickEntities;
    std::vector<std::string> targetNames;
    std::string currentTarget;
    float objectWidth = 100.0f;
    float objectHeight = 100.0f;

    int entityCount = 100;
    bool targetSpawned = false;

    std::vector<std::string> generateEntityList();
    bool isOverlapping(sf::FloatRect newRect, sf::FloatRect existingRect);
    sf::Vector2f getRandomNonOverlappingPosition(float padding);
};