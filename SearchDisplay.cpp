#include "SearchDisplay.h"
#include "GameObjectManager.h"
#include "BaseRunner.h"
#include "TextureManager.h"
#include "GameplayManager.h"

SearchDisplay::SearchDisplay(std::string name) : AGameObject(name) {
    // Initialize with sample targets or load from config
    this->targetNames = { "Topaz", "Sparkle", "Jingliu", "Aventurine", "Blade", "JingYuan", "Kafka", "March7th", "Rappa", "RuanMei"};
}

SearchDisplay::~SearchDisplay() {
    reset();
}

void SearchDisplay::initialize() {
    // Get actual dimensions from first texture
    sf::Texture* sampleTex = TextureManager::getInstance()->getFromTextureMap(targetNames[0], 0);
    if (sampleTex) {
        objectWidth = sampleTex->getSize().x * 0.4f;
        objectHeight = sampleTex->getSize().y * 0.4f; 
    }
}

void SearchDisplay::arrangeGrid(int columns, float padding) {
    reset();

    this->currentTarget = GameplayManager::getInstance()->getTarget();

    int rows = this->entityCount / columns + 1;
    float startX = (BaseRunner::WINDOW_WIDTH - (columns * (objectWidth + padding))) / 2;
    float startY = 100.0f; 

    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<int> dist(0, 9); 

    for (int i = 0; i < this->entityCount; i++) {
        int randomIndex = dist(engine);

        if (this->targetSpawned == true) {
            while (this->currentTarget == targetNames[randomIndex]) {
                randomIndex = dist(engine);
            }
        }

        ClickEntity* entity = new ClickEntity("SearchEntity_" + std::to_string(i), targetNames[randomIndex]);

        if (GameplayManager::getInstance()->getTarget() == targetNames[randomIndex])
            this->targetSpawned = true;

        // Calculate grid position
        int col = i % columns;
        int row = i / columns;
        float x = startX + col * (objectWidth + padding);
        float y = startY + row * (objectHeight + padding);

        entity->initialize();
        entity->setPosition(x, y);
        clickEntities.push_back(entity);
        GameObjectManager::getInstance()->addObject(entity);
    }
}

void SearchDisplay::scatterRandom(int areaPadding) {
    reset();

    for (int i = 0; i < this->entityCount; i++) {
        ClickEntity* entity = new ClickEntity("SearchEntity_" + std::to_string(i), targetNames[i]);
        entity->initialize();

        sf::Vector2f position = getRandomNonOverlappingPosition(areaPadding);
        entity->setPosition(position.x, position.y);

        clickEntities.push_back(entity);
        GameObjectManager::getInstance()->addObject(entity);
    }
}

void SearchDisplay::reset() {
    for (auto entity : clickEntities) {
        GameObjectManager::getInstance()->deleteObject(entity);
    }
    clickEntities.clear();
    this->targetSpawned = false;
}

void SearchDisplay::resetExceptTarget()
{
    std::vector<ClickEntity*> remainingEntities;

    for (auto entity : clickEntities) {
        if (entity->getTarget() == currentTarget) 
            remainingEntities.push_back(entity);
        
        else 
            GameObjectManager::getInstance()->deleteObject(entity);
    }

    clickEntities = remainingEntities;
}

void SearchDisplay::setEntityCount(int value)
{
    this->entityCount = value;
}

bool SearchDisplay::isOverlapping(sf::FloatRect newRect, sf::FloatRect existingRect) {
    return newRect.intersects(existingRect);
}

sf::Vector2f SearchDisplay::getRandomNonOverlappingPosition(float padding) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(padding, BaseRunner::WINDOW_WIDTH - objectWidth - padding);
    std::uniform_real_distribution<float> distY(padding, BaseRunner::WINDOW_HEIGHT - objectHeight - padding);

    sf::Vector2f position;
    bool validPosition = false;
    int attempts = 0;

    while (!validPosition && attempts < 100) {
        position = { distX(gen), distY(gen) };
        sf::FloatRect newBounds(position.x, position.y, objectWidth, objectHeight);

        validPosition = true;
        for (auto entity : clickEntities) {
            sf::FloatRect existingBounds = entity->getSprite()->getGlobalBounds();
            if (isOverlapping(newBounds, existingBounds)) {
                validPosition = false;
                break;
            }
        }
        attempts++;
    }

    return position;
}

void SearchDisplay::draw(sf::RenderWindow* targetWindow) {
    
}