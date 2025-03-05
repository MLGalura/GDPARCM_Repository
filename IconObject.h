#pragma once
#include "AGameObject.h"
class IconObject :    public AGameObject
{
public:
	IconObject(String name, int textureIndex);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

private:
	int textureIndex = 0;
	sf::IntRect frameRect;
	float elapsedTime = 0.0f;
	int currentFrame = 0;
	int frameWidth = 0;
	int frameHeight = 0;
};

