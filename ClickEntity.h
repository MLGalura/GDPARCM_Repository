#pragma once
#include "AGameObject.h"

class ClickEntity : public AGameObject
{
public:
	ClickEntity(String name, String initial);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void setTarget(std::string name);
	std::string getTarget();
	sf::Sprite* getSprite();

private:
	std::string targetName;

	int textureIndex = 0;
	sf::IntRect frameRect;
	int frameWidth = 0;
	int frameHeight = 0;

	bool isFlashing = false;
	float flashTimer = 0.0f;
	float sineWaveTime = 0.0f;
};

