#pragma once
#include "AGameObject.h"

class Target : public AGameObject
{
public:
	Target(String name, int textureIndex);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void callEnd();

	AGameObject::String getTarget();
	void setTarget(AGameObject::String name);

private:
	std::string targetName;
	bool end = false;

	int textureIndex = 0;
	sf::IntRect frameRect;
	int frameWidth = 0;
	int frameHeight = 0;
};

