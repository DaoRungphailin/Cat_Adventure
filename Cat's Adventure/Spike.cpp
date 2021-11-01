#include "stdafx.h"
#include "Spike.h"

void Spike::initSprite()
{
	this->spike.setTexture(this->spikeTex);
	this->spike.setScale(0.4f, 0.4f);
}

void Spike::initTexture()
{
	if (!this->spikeTex.loadFromFile("Textures/spike.PNG"))
	{
		std::cout << "ERROR::PLAYER::Could not load the spike sheet!" << "\n";
	}
}

Spike::~Spike()
{
}

Spike::Spike(float x, float y)
{
	this->initTexture();
	this->initSprite();
	this->setPosition(x, y);
}

const sf::Vector2f Spike::getPosition()
{
	return this->spike.getPosition();
}

const sf::FloatRect Spike::getGlobalbounds()
{
	return this->spike.getGlobalBounds();
}

void Spike::setPosition(float x, float y)
{
	this->spike.setPosition(x, y);
}

void Spike::update()
{
}

void Spike::updateMovement()
{
	this->spike.setPosition(spikeX, this->spike.getPosition().y);
	spikeX--;
}

void Spike::render(sf::RenderTarget& target)
{
	target.draw(this->spike);
}
