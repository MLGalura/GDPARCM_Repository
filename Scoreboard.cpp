#include "Scoreboard.h"
#include <iostream>
#include "BaseRunner.h"
#include "TextureManager.h"

Scoreboard::Scoreboard(String name) : AGameObject(name)
{
}

void Scoreboard::initialize()
{
    // Initialize the sprite with texture
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Scoreboard", this->textureIndex);
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

        // center the img
        this->posX = (BaseRunner::WINDOW_WIDTH - this->frameWidth * this->scaleX) / 2.0f;
        this->posY = -20.0f;
    }

    this->font = new sf::Font();
    this->font->loadFromFile("Media/Sansation.ttf");

    // same as fps counter, for the "Find this character"
    this->topText = new sf::Text();
    this->topText->setFont(*font);
    this->topText->setCharacterSize(16);
    this->topText->setFillColor(sf::Color::Yellow);
    this->topText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
    this->topText->setOutlineThickness(2.5f);
    this->topText->setPosition(BaseRunner::WINDOW_WIDTH / 2.1f, 60);
    this->topText->setString("Find this character!");

    // The actual score now
    this->scoreText = new sf::Text();
    this->scoreText->setFont(*font);
    this->scoreText->setCharacterSize(28);
    this->scoreText->setFillColor(sf::Color::White);
    this->scoreText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
    this->scoreText->setOutlineThickness(2.5f);
    this->scoreText->setPosition(BaseRunner::WINDOW_WIDTH / 2.1f, 80);
    this->scoreText->setString("Score: " + std::to_string(static_cast<int>(this->score))); 
}

void Scoreboard::processInput(sf::Event event)
{
}

void Scoreboard::update(sf::Time deltaTime)
{
    if (this->end) {
        this->posY -= 2.0f;

        this->topText->setString("");
        this->scoreText->setString("");
    }
}

void Scoreboard::draw(sf::RenderWindow* targetWindow)
{
    if (this->sprite != nullptr) {
        this->sprite->setPosition(this->posX, this->posY);
        this->sprite->setScale(this->scaleX, this->scaleY);

        targetWindow->draw(*this->sprite);
        targetWindow->draw(*this->topText);
        targetWindow->draw(*this->scoreText);
    }
}

void Scoreboard::callEnd()
{
    this->end = true;
}

void Scoreboard::setScore(int value)
{
    this->score = value;
    this->scoreText->setString("Score: " + std::to_string(static_cast<int>(this->score)));
}