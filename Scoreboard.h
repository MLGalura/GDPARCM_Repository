#pragma once
#include "AGameObject.h"

class Scoreboard : public AGameObject
{
public:
	Scoreboard(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* targetWindow) override;

	void callEnd();

	void setScore(int value);
	void setTarget();

private:
	int textureIndex = 0;
	sf::IntRect frameRect;
	int frameWidth = 0;
	int frameHeight = 0;

	int score = 0;
	bool end = false;

	sf::Text* topText;
	sf::Text* scoreText;
	sf::Font* font;
};

