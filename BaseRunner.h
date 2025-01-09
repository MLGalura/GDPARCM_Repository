#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include <iostream>

using namespace std;

class BaseRunner : private sf::NonCopyable
{
public:
	static const sf::Time TIME_PER_FRAME;
	static const int WINDOW_HEIGHT = 1920; 
	static const int WINDOW_WIDTH  = 1080;

	BaseRunner();
	void run();

	static BaseRunner* getInstance();
	static BaseRunner* sharedInstance;

	float getFPS();

private:
	sf::RenderWindow window;
	float fps = 0.0f;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);
};

