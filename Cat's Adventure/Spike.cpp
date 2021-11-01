#include "stdafx.h"
#include "Spike.h"

void Spike::initHitbox()
{
	spikeHitbox.setOutlineColor(sf::Color::Red);
	spikeHitbox.setOutlineThickness(2.f);
	spikeHitbox.setFillColor(sf::Color::Transparent);
	spikeHitbox.setSize(sf::Vector2f(75.f, 50.f));
}

void Spike::initSprite()
{
	this->spike.setTexture(this->spikeTex);
	this->spike.setScale(0.2f, 0.2f);
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
	this->initHitbox();
	this->initTexture();
	this->initSprite();
	this->setPosition(x, y);
	spikeX = x;
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

const sf::FloatRect Spike::getGlobalBoundsHitbox() const
{
	return this->spikeHitbox.getGlobalBounds();
}

void Spike::update()
{
	this->updateHitbox();
	this->updateMovement();
}

void Spike::updateHitbox()
{
	spikeHitbox.setPosition(spike.getPosition().x, spike.getPosition().y);
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
