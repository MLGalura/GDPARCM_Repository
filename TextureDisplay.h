#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include <iostream>
#include <filesystem>

using namespace std;

class TextureDisplay
{
public:
	TextureDisplay();
	~TextureDisplay();

	void initialize();
	void processInput();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* targetWindow);

private:
	const float TIME_TO_DISPLAY = 0.15f;
	const int IMAGE_SIZE = 50;
	const int SPACING = 15;

	vector<sf::Texture> textures;
	vector<sf::Sprite> sprites;
	vector<string> filePaths; 

	size_t currentSpriteIndex = 0;
	sf::Time elapsedTime;
	sf::Vector2f position;
};

