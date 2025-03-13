#include "BaseRunner.h"

#include <iostream>

#include  "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "SoundManager.h"
#include "FPSCounter.h"
#include "LoadPercentage.h"

#include "Scoreboard.h"
#include "Target.h"

const float FRAME_RATE = 60.0f;
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.0f / FRAME_RATE);
BaseRunner* BaseRunner::sharedInstance = NULL;

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GALURA - Interactive Loading Screen", sf::Style::Close) {

	sharedInstance = this;
	this->window.setFramerateLimit(int(FRAME_RATE));
	
	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();
	SoundManager::getInstance()->loadMusic("HanuTheme.mp3");
	SoundManager::getInstance()->setMusicVolume(30);
	SoundManager::getInstance()->playMusic(true);

	//load objects
	//BGObject* bgObject = new BGObject("BGObject");
	//GameObjectManager::getInstance()->addObject(bgObject);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);

	LoadPercentage* loadPercentage = new LoadPercentage();
	GameObjectManager::getInstance()->addObject(loadPercentage);

	Scoreboard* scoreboard = new Scoreboard("scoreboard", 0);
	GameObjectManager::getInstance()->addObject(scoreboard);
	
	Target* target = new Target("target", 0);
	GameObjectManager::getInstance()->addObject(target);
}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	while (this->window.isOpen())
	{
		currentTime = clock.getElapsedTime();
		float deltaTime = currentTime.asSeconds() - previousTime.asSeconds();
		this->fps = floor(1.0f / deltaTime);

		processEvents();
		update(sf::seconds(1.0f / this->fps));
		render();
		
		previousTime = currentTime;
		
		
	}
}

BaseRunner* BaseRunner::getInstance()
{
	return sharedInstance;
}

float BaseRunner::getFPS() const
{
	return this->fps;
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Space) {
				GameObjectManager::getInstance()->DoShowFinalAssets();
				GameObjectManager::getInstance()->deleteObjectByName("LoadPercentage");
			}

			if (event.key.code == sf::Keyboard::A) {
				Target* targetobj = dynamic_cast<Target*>(GameObjectManager::getInstance()->findObjectByName("target"));
				targetobj->setTarget("Topaz");
			}
			break;
		
		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;

		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}