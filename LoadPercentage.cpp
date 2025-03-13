#include "LoadPercentage.h"
#include "GameObjectManager.h"
#include "IconObject.h"
#include "BaseRunner.h"

LoadPercentage::LoadPercentage() : AGameObject("LoadPercentage") {
}

LoadPercentage::~LoadPercentage() {
    delete this->font;
    delete this->loadingText;
}

void LoadPercentage::initialize() {
    // Count total files in directory
    for (const auto& entry : std::filesystem::directory_iterator(SPECIAL_PATH)) {
        totalFiles++;
    }

    // Initialize text display
    this->font = new sf::Font();
    this->font->loadFromFile("Media/Sansation.ttf");

    // Same as fpscounter
    this->loadingText = new sf::Text();
    this->loadingText->setFont(*font);
    this->loadingText->setCharacterSize(24);
    this->loadingText->setFillColor(sf::Color::White);
    this->loadingText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
    this->loadingText->setOutlineThickness(1.5f);
    this->loadingText->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f, BaseRunner::WINDOW_HEIGHT - 80);
    this->loadingText->setOrigin(this->loadingText->getLocalBounds().width / 2.0f, 0);
    this->loadingText->setString("Loading: 0%");
}

void LoadPercentage::update(sf::Time deltaTime) {
    updatePercentage();

    if (isComplete) {
        // Sine wave for opacity flashin
        sineWaveTime += deltaTime.asSeconds();

        // Calculate opacity
        float opacity = 0.65f + 0.35f * sin(sineWaveTime * 3.0f);
        sf::Color textColor = this->loadingText->getFillColor();
        sf::Color outlineColor = this->loadingText->getOutlineColor();
        textColor.a = static_cast<sf::Uint8>(opacity * 255);
        outlineColor.a = static_cast<sf::Uint8>(opacity * 255);
        this->loadingText->setFillColor(textColor);
        this->loadingText->setOutlineColor(outlineColor);
    }
} 

void LoadPercentage::draw(sf::RenderWindow* targetWindow) {
    targetWindow->draw(*this->loadingText);
}

bool LoadPercentage::IsComplete()
{
    return this->isComplete;
}

void LoadPercentage::updatePercentage() {
    int loadedCount = 0;
    auto allObjects = GameObjectManager::getInstance()->getAllFinalObjects();

    // Just to check icon objects, the final loaded assets
    for (auto obj : allObjects) {
        if (dynamic_cast<IconObject*>(obj) != nullptr) {
            loadedCount++;
        }
    }

    float percentage = (totalFiles > 0) ?
        ((static_cast<float>(loadedCount) / totalFiles) * 100.0f) :
        0.0f;

    if (percentage >= 100.0f) {
        isComplete = true;
        this->loadingText->setString("Press Space To Continue");
    }

    else 
        this->loadingText->setString("Loading: " + std::to_string(static_cast<int>(percentage)) + "%");

    // Simple centerer
    sf::FloatRect textBounds = this->loadingText->getLocalBounds();
    this->loadingText->setOrigin(textBounds.width / 2.0f, 0);
    
}