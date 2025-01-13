#include "BaseRunner.h"
#include "FPSCounter.h"
#include "BGObject.h"
#include "TextureDisplay.h"

BaseRunner::BaseRunner()
{
}

void BaseRunner::run()
{
	cout << "BaseRunner.cpp run initialization successful." << endl; 

	sf::RenderWindow window(sf::VideoMode(this->WINDOW_WIDTH, this->WINDOW_HEIGHT), "Marc's Application");

	BGObject bg;
	bg.initialize();

	TextureDisplay td;
	td.initialize();

	FPSCounter counter;
	counter.initialize();

	sf::Clock clock; //Clocc

	while (window.isOpen()) {
		sf::Time elapsedTime = clock.restart(); 
		this->fps = 1.0f / elapsedTime.asSeconds();   

		bg.update(elapsedTime);
		td.update(elapsedTime);
		counter.update(elapsedTime);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		bg.draw(&window);
		td.draw(&window);
		counter.draw(&window);
		window.display();
	}
}

BaseRunner* BaseRunner::getInstance()
{
	static BaseRunner instance;
	return &instance;
}

float BaseRunner::getFPS()
{
	return this->fps;
}

void BaseRunner::render()
{
}

void BaseRunner::processEvents()
{
}

void BaseRunner::update(sf::Time elapsedTime)
{
}
