#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include <iostream>

using namespace std;

class BGObject
{
public:
	BGObject();
	~BGObject();

	void initialize();
	void processInput();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* targetWindow);

private:
	static const int SPEED_MULTIPLIER = 50;

	sf::Sprite sprite;
	sf::Texture texture;
};

