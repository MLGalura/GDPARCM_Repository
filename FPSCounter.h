#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include <iostream>
#include "BaseRunner.h"

using namespace std;

class FPSCounter
{
public:
	FPSCounter();
	~FPSCounter();

	void initialize();
	void processInput();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* targetWindow);

private:
	sf::Time updateTime;
	sf::Text* statsText;

	void updateFPS(sf::Time elapsedTime);
};

