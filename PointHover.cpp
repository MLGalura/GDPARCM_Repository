#include "PointHover.h"
#include "GameObjectManager.h"
#include "ClickEntity.h"
#include "BaseRunner.h"

PointHover::PointHover() : AGameObject("PointHover")
{
}

PointHover::~PointHover()
{
	delete this->font;
	delete this->pointText;
}

void PointHover::initialize()
{
    // Initialize text display
    this->font = new sf::Font();
    this->font->loadFromFile("Media/Sansation.ttf");

    // Same as fpscounter
    this->pointText = new sf::Text();
    this->pointText->setFont(*font);
    this->pointText->setCharacterSize(30);
    this->pointText->setFillColor(sf::Color::Green);
    this->pointText->setOutlineColor(sf::Color::White);
    this->pointText->setOutlineThickness(2.5f);
    this->pointText->setPosition(0.0f, 0.0f);
    this->pointText->setString("+0");
}

void PointHover::update(sf::Time deltaTime)
{
    if (this->isVisible) {
        this->timer += deltaTime.asSeconds();

        if (this->timer < 1.5f) {
            this->posY -= 1.0f;
            this->pointText->setPosition(this->posX, this->posY);
        }

        else {
            this->timer = 0.0f;
            this->isVisible = false;
        }
    }
}

void PointHover::draw(sf::RenderWindow* targetWindow)
{
    if (this->isVisible)
        targetWindow->draw(*this->pointText);
}

bool PointHover::showPoint()
{
    this->timer = 0.0f;

    return this->isVisible = true;
}

void PointHover::setPosition(float posX, float posY)
{
    this->posX = posX;
    this->posY = posY;

    this->pointText->setPosition(this->posX, this->posY);
}

void PointHover::setPoints(std::string points, sf::Color color)
{
    this->pointText->setFillColor(color);
    this->pointText->setString(points);
}
