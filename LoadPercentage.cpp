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
    this->font->loadFromFile("Media/Sansation.ttf"); // Ensure this path matches your font

    this->loadingText = new sf::Text();
    this->loadingText->setFont(*font);
    this->loadingText->setCharacterSize(24);
    this->loadingText->setFillColor(sf::Color::White);
    this->loadingText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
    this->loadingText->setPosition(BaseRunner::WINDOW_WIDTH / 2.0f, BaseRunner::WINDOW_HEIGHT - 70);
    this->loadingText->setString("Loading: 0%");
}

void LoadPercentage::update(sf::Time deltaTime) {
    updatePercentage();
}

void LoadPercentage::draw(sf::RenderWindow* targetWindow) {
    targetWindow->draw(*this->loadingText);
}

void LoadPercentage::updatePercentage() {
    int loadedCount = 0;
    auto allObjects = GameObjectManager::getInstance()->getAllFinalObjects();

    for (auto obj : allObjects) {
        if (dynamic_cast<IconObject*>(obj) != nullptr) {
            loadedCount++;
        }
    }

    float percentage = (totalFiles > 0) ?
        ((static_cast<float>(loadedCount) / totalFiles) * 100.0f) :
        0.0f;

    this->loadingText->setString("Loading: " + std::to_string(static_cast<int>(percentage)) + "%");
}