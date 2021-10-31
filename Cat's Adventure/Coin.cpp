#include "stdafx.h"
#include "coin.h"

void Coin::initSprite()
{
	this->coin.setTexture(this->coinTex);
	this->currentFrame = sf::IntRect(0, 0, 135, 405);
	this->coin.setTextureRect(this->currentFrame);
	this->coin.setScale(0.4f, 0.4f);
}

void Coin::initTexture()
{
	if (!this->coinTex.loadFromFile("Textures/coin.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
	}
}

void Coin::initAnimation()
{
	this->animationTimer.restart();
}

void Coin::updateAnimation()
{
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
	{
		this->currentFrame.top = 0.f;
		this->currentFrame.left += 135.f;
		if (this->currentFrame.left >= 810.f)
			this->currentFrame.left = 0;
		this->animationTimer.restart();
		this->coin.setTextureRect(this->currentFrame);
	}
}

void Coin::updateMovement()
{
	this->coin.setPosition(coinX, this->coin.getPosition().y);
	coinX--;
}

Coin::~Coin()
{
}

Coin::Coin(float x, float y)
{
	this->initTexture();
	this->initSprite();
	this->initAnimation();
	this->setPosition(x, y);
	coinX = x;
}

const sf::Vector2f Coin::getPosition()
{
	return this->coin.getPosition();
}

const sf::FloatRect Coin::getGlobalbounds()
{
	return this->coin.getGlobalBounds();
}

void Coin::setPosition(float x, float y)
{
	this->coin.setPosition(x, y);
}

void Coin::update()
{
	this->updateAnimation();
	this->updateMovement();
}

void Coin::render(sf::RenderTarget& target)
{
	target.draw(this->coin);
}
