#include "ClickEntity.h"
#include <iostream>
#include "BaseRunner.h"
#include "TextureManager.h"
#include "GameplayManager.h"
#include "GameObjectManager.h"
#include "SoundManager.h"

ClickEntity::ClickEntity(String name, String initial) : AGameObject(name)
{
    this->textureIndex = textureIndex;
    this->targetName = initial;
}

void ClickEntity::initialize()
{
    // Initialize the sprite with texture
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(this->targetName, this->textureIndex);
    if (texture) {
        this->sprite = new sf::Sprite();
        this->sprite->setTexture(*texture);

        // Set frame size
        this->frameWidth = texture->getSize().x;
        this->frameHeight = texture->getSize().y;
        this->frameRect = sf::IntRect(0, 0, this->frameWidth, this->frameHeight);
        this->sprite->setTextureRect(this->frameRect);

        this->scaleX = 0.4f;
        this->scaleY = 0.4f;
    }
}

void ClickEntity::processInput(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (this->sprite && this->sprite->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            if (!isFlashing) {
                if (GameplayManager::getInstance()->getTarget() == this->targetName) {
                    SoundManager::getInstance()->playSound(GameplayManager::getInstance()->getTarget() + "Success");
                    GameplayManager::getInstance()->setScore(GameplayManager::getInstance()->getScore() + 10);
                    GameplayManager::getInstance()->winRound();

                    this->isFlashing = true;
                }

                else {
                    SoundManager::getInstance()->playSound(GameplayManager::getInstance()->getTarget() + "Fail");
                    GameplayManager::getInstance()->setScore(GameplayManager::getInstance()->getScore() - 5);
                    this->isFlashing = true;
                }
            }
        }
    }
}

void ClickEntity::update(sf::Time deltaTime)
{
    if (this->isFlashing) {
        this->flashTimer += deltaTime.asSeconds();
        this->sineWaveTime += deltaTime.asSeconds() * 15.0f;

        if (this->flashTimer >= 2.4f) {
            this->isFlashing = false;
            this->flashTimer = 0.0f;
            this->sineWaveTime = 0.0f;

            sf::Color color = this->sprite->getColor();
            color.a = 255;
            this->sprite->setColor(color);
        }
        else {
            // sine wave
            float opacity = (sin(this->sineWaveTime) + 1.0f) / 2.0f;
            sf::Color color = this->sprite->getColor();
            color.a = static_cast<sf::Uint8>(opacity * 255);
            this->sprite->setColor(color);
        }
    }

    if (this->end) {
        float opacity = this->sprite->getColor().a / 255.0f; 
        opacity = std::max(0.0f, opacity - 0.01f);  
        sf::Color color = this->sprite->getColor();
        color.a = static_cast<sf::Uint8>(opacity * 255);
        this->sprite->setColor(color);

        if (opacity <= 0)
            GameObjectManager::getInstance()->deleteObject(this);
    }
}

void ClickEntity::setTarget(std::string name)
{
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(name, this->textureIndex);
    this->sprite->setTexture(*texture);

    this->targetName = name;
}

std::string ClickEntity::getTarget()
{
    return this->targetName;
}

sf::Sprite* ClickEntity::getSprite()
{
    return this->sprite;
}

void ClickEntity::callEnd()
{
    this->end = true;
}
