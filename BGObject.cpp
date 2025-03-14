#include "BGObject.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"

BGObject::BGObject(string name) : AGameObject(name)
{
}

void BGObject::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Penacony", 0);
	if (texture) {
		this->sprite = new sf::Sprite();
		this->sprite->setTexture(*texture);

		// Set frame size
		this->frameWidth = texture->getSize().x;
		this->frameHeight = texture->getSize().y;
		this->frameRect = sf::IntRect(0, 0, this->frameWidth, this->frameHeight);
		this->sprite->setTextureRect(this->frameRect);

		this->scaleX = 0.3f;
		this->scaleY = 0.3f;

	}

	// start transparent
	sf::Color color = this->sprite->getColor();
	color.a = 0;
	this->sprite->setColor(color);
}

void BGObject::processInput(sf::Event event)
{
}

void BGObject::update(sf::Time deltaTime)
{
	if (this->show) {
		this->timer += deltaTime.asSeconds();

		if (this->timer > 2.0f) {
			float opacity = this->sprite->getColor().a / 255.0f;
			opacity = std::min(1.0f, opacity + 0.01f);
			sf::Color color = this->sprite->getColor();
			color.a = static_cast<sf::Uint8>(opacity * 255);
			this->sprite->setColor(color);
		}
	}
	//make BG scroll slowly
	//sf::Vector2f position = this->getPosition();
	//position.y += this->SPEED_MULTIPLIER * deltaTime.asSeconds();
	//this->setPosition(position.x, position.y);

	//sf::Vector2f localPos = this->sprite->getPosition();
	//if (localPos.y * deltaTime.asSeconds() > 0) {
	//	//reset position
	//	this->setPosition(0, -BaseRunner::WINDOW_HEIGHT * 7);
	//}
	//else {
	//	
	//}
}

void BGObject::showBG()
{
	this->show = true;
}
