#include "Target.h"
#include <iostream>
#include "BaseRunner.h"
#include "TextureManager.h"

Target::Target(String name, int textureIndex) : AGameObject(name)
{
	this->textureIndex = textureIndex;
}

void Target::initialize()
{
    // Initialize the sprite with texture
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Sparkle", this->textureIndex);
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

        // center the img
        this->posX = (BaseRunner::WINDOW_WIDTH - this->frameWidth * this->scaleX) / 2.275f;
        this->posY = 40.0f;
    }
}

void Target::processInput(sf::Event event)
{
}

void Target::update(sf::Time deltaTime)
{
    if (this->end) {
        this->posY -= 2.0f;
    }
}

void Target::callEnd()
{
    this->end = true;
}

AGameObject::String Target::getTarget()
{
    return this->targetName;
}

void Target::setTarget(AGameObject::String name)
{
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(name, this->textureIndex);
    this->sprite->setTexture(*texture);

    this->targetName = name;
}
