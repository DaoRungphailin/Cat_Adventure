#include "stdafx.h"
#include "HeartItem.h"

void HeartItem::initHitbox()
{
	this->heartHitbox.setOutlineColor(sf::Color::Magenta);
	this->heartHitbox.setOutlineThickness(2.f);
	this->heartHitbox.setFillColor(sf::Color::Transparent);
	this->heartHitbox.setSize(sf::Vector2f(57.f, 55.f));
}

void HeartItem::initSprite()
{
	this->heart.setTexture(this->heartTex);
}

void HeartItem::initTexture()
{
	if (!this->heartTex.loadFromFile("Textures/boostHp.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the boostHp sheet!" << "\n";
	}
}

void HeartItem::updateHitbox()
{
	this->heartHitbox.setPosition(heart.getPosition().x + 2.5f, heart.getPosition().y + 2.f);
}

void HeartItem::updateMovement()
{
	this->heart.setPosition(heartX, this->heart.getPosition().y);
	heartX--;
}

HeartItem::~HeartItem()
{
}

HeartItem::HeartItem(float x, float y)
{
	this->initHitbox();
	this->initTexture();
	this->initSprite();
	this->setPosition(x, y);

	heartX = x;
}

const sf::Vector2f HeartItem::getPosition()
{
	return this->heart.getPosition();
}

const sf::FloatRect HeartItem::getGlobalbounds() const
{
	return this->heart.getGlobalBounds();
}

void HeartItem::setPosition(float x, float y)
{
	this->heart.setPosition(x, y);
}

const sf::FloatRect HeartItem::getGlobalBoundsHitbox() const
{
	return this->heartHitbox.getGlobalBounds();
}

void HeartItem::update()
{
	this->updateMovement();
	this->updateHitbox();
}

void HeartItem::render(sf::RenderTarget& target)
{
	target.draw(this->heart);
	//target.draw(this->heartHitbox);
}
