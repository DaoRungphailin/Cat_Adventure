#include "stdafx.h"
#include "Shield.h"

void Shield::initHitbox()
{
	this->shieldHitbox.setOutlineColor(sf::Color::Blue);
	this->shieldHitbox.setOutlineThickness(2.f);
	this->shieldHitbox.setFillColor(sf::Color::Transparent);
	this->shieldHitbox.setSize(sf::Vector2f(70.f, 80.f));
}

void Shield::initSprite()
{
	this->shield.setTexture(this->shieldTex);
}

void Shield::initTexture()
{
	if (!this->shieldTex.loadFromFile("Textures/shield.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the boostHp sheet!" << "\n";
	}
}

void Shield::updateHitbox()
{
	this->shieldHitbox.setPosition(shield.getPosition().x + 2.5f, shield.getPosition().y + 2.f);
}

void Shield::updateMovement()
{
	this->shield.setPosition(shieldX, this->shield.getPosition().y);
	shieldX--;
}

Shield::~Shield()
{
}

Shield::Shield(float x, float y)
{
	this->initHitbox();
	this->initTexture();
	this->initSprite();
	this->setPosition(x, y);

	shieldX = x;
}

const sf::Vector2f Shield::getPosition()
{
	return this->shield.getPosition();
}

const sf::FloatRect Shield::getGlobalbounds() const
{
	return this->shield.getGlobalBounds();
}

void Shield::setPosition(float x, float y)
{
	this->shield.setPosition(x, y);
}

const sf::FloatRect Shield::getGlobalBoundsHitbox() const
{
	return this->shieldHitbox.getGlobalBounds();
}

void Shield::update()
{
	this->updateMovement();
	this->updateHitbox();
}

void Shield::render(sf::RenderTarget& target)
{
	target.draw(this->shield);
	target.draw(this->shieldHitbox);
}
