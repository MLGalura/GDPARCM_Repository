#include "FPSCounter.h"

FPSCounter::FPSCounter()
{
}

FPSCounter::~FPSCounter()
{
	delete this->statsText->getFont();
	delete this->statsText;
}

void FPSCounter::initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	this->statsText = new sf::Text();
	this->statsText->setFont(*font);
	this->statsText->setPosition(BaseRunner::WINDOW_WIDTH - 200, BaseRunner::WINDOW_HEIGHT - 160);
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->statsText->setOutlineThickness(2.5f);
	this->statsText->setCharacterSize(35);

	cout << "FPS Counter initialized successfully." << endl;
}

void FPSCounter::processInput()
{
}

void FPSCounter::update(sf::Time deltaTime)
{
	this->updateFPS(deltaTime);
}

void FPSCounter::draw(sf::RenderWindow* targetWindow)
{
	if (this->statsText != nullptr) {
		targetWindow->draw(*this->statsText);
	}
}

void FPSCounter::updateFPS(sf::Time elapsedTime)
{
	this->updateTime += elapsedTime;

	if (this->updateTime >= sf::seconds(0.25f)) {
		this->updateTime = sf::seconds(0.0f);
		
		// To show FPS as whole number
		int fps = static_cast<int>(BaseRunner::getInstance()->getFPS());
		
		// Just to cap fps at 60 frames
		if (fps > 60) fps = 60;

		this->statsText->setString("FPS: " + std::to_string(fps));
	}
}
