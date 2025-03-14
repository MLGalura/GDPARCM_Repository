#pragma once
#include "AGameObject.h"
#include <SFML/Graphics.hpp>
#include <filesystem>

class PointHover : public AGameObject {
public:
    PointHover();
    ~PointHover();

    void initialize() override;
    void processInput(sf::Event event) override {};
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow* targetWindow) override;

    bool showPoint();
    void setPosition(float posX, float posY);
    void setPoints(std::string points, sf::Color color);

private:
    sf::Text* pointText;
    sf::Font* font;

    bool isVisible = false;
    float timer = 0.0f;
};