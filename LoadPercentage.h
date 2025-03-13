#pragma once
#include "AGameObject.h"
#include <SFML/Graphics.hpp>
#include <filesystem>

class LoadPercentage : public AGameObject {
public:
    LoadPercentage();
    ~LoadPercentage();

    void initialize() override;
    void processInput(sf::Event event) override {};
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow* targetWindow) override;

private:
    sf::Text* loadingText;
    sf::Font* font;
    int totalFiles = 0;
    const std::string SPECIAL_PATH = "Media/40MB/";

    void updatePercentage();

    bool isComplete = false; 
    float sineWaveTime = 0.0f;
};