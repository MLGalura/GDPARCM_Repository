#include "BaseRunner.h"

BaseRunner::BaseRunner()
{
}

void BaseRunner::run()
{
	cout << "what" << endl; 

}

BaseRunner* BaseRunner::getInstance()
{
	return nullptr;
}

float BaseRunner::getFPS()
{
	return 0.0f;
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
