#include "IconObject.h"
#include <iostream>
#include "BaseRunner.h"
#include "TextureManager.h"

IconObject::IconObject(String name, int textureIndex) : AGameObject(name) {
    this->textureIndex = textureIndex;
    this->elapsedTime = 0.0f;
    this->currentFrame = 0;
}

void IconObject::initialize() {
    // Initialize the sprite with texture
    sf::Texture* texture = TextureManager::getInstance()->getStreamTextureFromList(this->textureIndex);
    if (texture) {
        this->sprite = new sf::Sprite();
        this->sprite->setTexture(*texture);

        // Set frame size
        this->frameWidth = texture->getSize().x / 10; 
        this->frameHeight = texture->getSize().y / 5; 
        this->frameRect = sf::IntRect(0, 0, this->frameWidth, this->frameHeight);
        this->sprite->setTextureRect(this->frameRect);

        // start transparent
        sf::Color color = this->sprite->getColor();
        color.a = 0;
        this->sprite->setColor(color);
    }
}

void IconObject::processInput(sf::Event event) {
}

void IconObject::update(sf::Time deltaTime) {

    this->timer += deltaTime.asSeconds();

    if (this->timer > 2.0f) {
        float opacity = this->sprite->getColor().a / 255.0f;
        opacity = std::min(1.0f, opacity + 0.01f);
        sf::Color color = this->sprite->getColor();
        color.a = static_cast<sf::Uint8>(opacity * 255);
        this->sprite->setColor(color);
    }
    
    // handle animation
    float animationSpeed = 0.1f;
    this->elapsedTime += deltaTime.asSeconds();

    if (this->elapsedTime >= animationSpeed) {
        this->elapsedTime = 0.0f;
        this->currentFrame = (this->currentFrame + 1) % (10 * 5);

        int column = this->currentFrame % 10;
        int row = this->currentFrame / 10;
        this->frameRect.left = column * this->frameWidth;
        this->frameRect.top = row * this->frameHeight;
        this->sprite->setTextureRect(this->frameRect);
    }
}

