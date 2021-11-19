#include "stdafx.h"
#include "Bomb.h"

void Bomb::initHitbox()
{
	this->bombHitbox.setOutlineColor(sf::Color::Magenta);
	this->bombHitbox.setOutlineThickness(2.f);
	this->bombHitbox.setFillColor(sf::Color::Transparent);
	this->bombHitbox.setSize(sf::Vector2f(57.f, 77.f));
}

void Bomb::initSprite()
{
	this->bomb.setTexture(this->bombTex);
}

void Bomb::initTexture()
{
	if (!this->bombTex.loadFromFile("Textures/bomb.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the boostHp sheet!" << "\n";
	}
}

void Bomb::updateHitbox()
{
	this->bombHitbox.setPosition(bomb.getPosition().x + 2.5f, bomb.getPosition().y + 2.f);
}

void Bomb::updateMovement()
{
	this->bomb.setPosition(bombX, this->bomb.getPosition().y);
	bombX--;
}

Bomb::~Bomb()
{
}

Bomb::Bomb(float x, float y)
{
	this->initHitbox();
	this->initTexture();
	this->initSprite();
	this->setPosition(x, y);

	bombX = x;
}

const sf::Vector2f Bomb::getPosition()
{
	return this->bomb.getPosition();
}

const sf::FloatRect Bomb::getGlobalbounds() const
{
	return this->bomb.getGlobalBounds();
}

void Bomb::setPosition(float x, float y)
{
	this->bomb.setPosition(x, y);
}

const sf::FloatRect Bomb::getGlobalBoundsHitbox() const
{
	return this->bombHitbox.getGlobalBounds();
}

void Bomb::update()
{
	this->updateMovement();
	this->updateHitbox();
}

void Bomb::render(sf::RenderTarget& target)
{
	target.draw(this->bomb);
	//target.draw(this->bombHitbox);
}
