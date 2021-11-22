#include "stdafx.h"
#include "Magnet.h"

void Magnet::initHitbox()
{
	this->magnetHitbox.setOutlineColor(sf::Color::Yellow);
	this->magnetHitbox.setOutlineThickness(2.f);
	this->magnetHitbox.setFillColor(sf::Color::Transparent);
	this->magnetHitbox.setSize(sf::Vector2f(50.f, 50.f));
}

void Magnet::initSprite()
{
	this->magnet.setTexture(this->magnetTex);
}

void Magnet::initTexture()
{
	if (!this->magnetTex.loadFromFile("Textures/magnet.PNG"))
	{
		std::cout << "ERROR::PLAYER::Could not load the magnet sheet!" << "\n";
	}
}

void Magnet::updateHitbox()
{
	this->magnetHitbox.setPosition(magnet.getPosition().x + 2.5f, magnet.getPosition().y + 2.f);
}

void Magnet::updateMovement()
{
	this->magnet.setPosition(magnetX, this->magnet.getPosition().y);
	magnetX--;
}

Magnet::~Magnet()
{
}

Magnet::Magnet(float x, float y)
{
	this->initHitbox();
	this->initTexture();
	this->initSprite();
	this->setPosition(x, y);

	magnetX = x;
}

const sf::Vector2f Magnet::getPosition()
{
	return this->magnet.getPosition();
}

const sf::FloatRect Magnet::getGlobalbounds() const
{
	return this->magnet.getGlobalBounds();
}

void Magnet::setPosition(float x, float y)
{
	this->magnet.setPosition(x, y);
}

const sf::FloatRect Magnet::getGlobalBoundsHitbox() const
{
	return this->magnetHitbox.getGlobalBounds();
}

void Magnet::update()
{
	this->updateMovement();
	this->updateHitbox();
}

void Magnet::render(sf::RenderTarget& target)
{
	target.draw(this->magnet);
	//target.draw(this->magnetHitbox);
}
