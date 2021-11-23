#include "stdafx.h"
#include "Bonus.h"

void Bonus::initHitbox()
{
	this->giftHitbox.setOutlineColor(sf::Color::Yellow);
	this->giftHitbox.setOutlineThickness(2.f);
	this->giftHitbox.setFillColor(sf::Color::Transparent);
	this->giftHitbox.setSize(sf::Vector2f(80.f, 80.f));
}

void Bonus::initSprite()
{
	this->gift.setTexture(this->giftTex);
	this->gift.setScale(0.2f, 0.2f);
}

void Bonus::initTexture()
{
	if (!this->giftTex.loadFromFile("Textures/gift.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the gift sheet!" << "\n";
	}
}

void Bonus::updateHitbox()
{
	this->giftHitbox.setPosition(gift.getPosition().x + 2.5f, gift.getPosition().y + 2.f);
}

void Bonus::updateMovement()
{
	this->gift.setPosition(giftX, this->gift.getPosition().y);
	giftX--;
}

Bonus::~Bonus()
{
}

Bonus::Bonus(float x, float y)
{

	this->initHitbox();
	this->initTexture();
	this->initSprite();
	this->setPosition(x, y);

	giftX = x;
}

const sf::Vector2f Bonus::getPosition()
{
	return this->gift.getPosition();
}

const sf::FloatRect Bonus::getGlobalbounds() const
{
	return this->gift.getGlobalBounds();
}

void Bonus::setPosition(float x, float y)
{
	this->gift.setPosition(x, y);
}

const sf::FloatRect Bonus::getGlobalBoundsHitbox() const
{
	return this->giftHitbox.getGlobalBounds();
}

void Bonus::update()
{
	this->updateMovement();
	this->updateHitbox();
}

void Bonus::render(sf::RenderTarget& target)
{
	target.draw(this->gift);
	//target.draw(this->giftHitbox);
}
