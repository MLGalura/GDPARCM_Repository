#include "ClickEntity.h"
#include <iostream>
#include "BaseRunner.h"
#include "TextureManager.h"

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
        if (this->sprite && this->sprite->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            this->setTarget("Rappa");
    }
}

void ClickEntity::update(sf::Time deltaTime)
{
}

void ClickEntity::setTarget(std::string name)
{
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(name, this->textureIndex);
    this->sprite->setTexture(*texture);

    this->targetName = name;
}
