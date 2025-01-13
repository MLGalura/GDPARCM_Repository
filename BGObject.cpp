#include "BGObject.h"
#include "BaseRunner.h"

BGObject::BGObject()
{
}

BGObject::~BGObject()
{
}

void BGObject::initialize()
{
	if (!this->texture.loadFromFile("Media/Textures/Desert.png")) {
		cout << "Could not load texture." << endl;
		return;
	}

	this->texture.setRepeated(true);
	this->sprite.setTexture(this->texture);

	sf::Vector2u textureSize = this->sprite.getTexture()->getSize();
	this->sprite.setTextureRect(sf::IntRect(0, 0, BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT * 8));
	this->sprite.setPosition(0, -BaseRunner::WINDOW_HEIGHT * 7);
}

void BGObject::processInput()
{
}

void BGObject::update(sf::Time deltaTime)
{
	sf::Vector2f position = this->sprite.getPosition();
	position.y += this->SPEED_MULTIPLIER * deltaTime.asSeconds();

	this->sprite.setPosition(position.x, position.y);

	sf::Vector2f localPos = this->sprite.getPosition();
	if (localPos.y * deltaTime.asSeconds() > 0)
		this->sprite.setPosition(0, -BaseRunner::WINDOW_HEIGHT * 7);
}

void BGObject::draw(sf::RenderWindow* targetWindow)
{
	targetWindow->draw(this->sprite);
}
