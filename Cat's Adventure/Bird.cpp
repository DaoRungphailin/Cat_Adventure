#include "stdafx.h"
#include "Bird.h"

void Bird::initTexture()
{
	if (!this->birdTex.loadFromFile("Textures/blue bird.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the bird sheet!" << "\n";
	}
}

void Bird::initSprite()
{
	this->bird.setTexture(this->birdTex);
	this->currentFrame = sf::IntRect(0, 0, 200.5, 141);
	this->bird.setTextureRect(this->currentFrame);
	//this->bird.setScale(0.4f, 0.4f);
}

void Bird::initAnimation()
{
	this->animationTimer.restart();
}

void Bird::initHitbox()
{
	this->birdHitbox.setOutlineColor(sf::Color::Cyan);
	this->birdHitbox.setOutlineThickness(2.f);
	this->birdHitbox.setFillColor(sf::Color::Transparent);
	this->birdHitbox.setSize(sf::Vector2f(185.f, 135.f));
}

void Bird::updateHitbox()
{
	this->birdHitbox.setPosition(bird.getPosition().x, bird.getPosition().y);
}

void Bird::updateMovement()
{
	this->bird.setPosition(birdX, this->bird.getPosition().y);
	birdX -= 2;
}

void Bird::updateAnimation()
{
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
	{
		this->currentFrame.top = 0.f;
		this->currentFrame.left += 200.5f;
		if (this->currentFrame.left >= 800.f)
			this->currentFrame.left = 0;
		this->animationTimer.restart();
		this->bird.setTextureRect(this->currentFrame);
	}
}

Bird::Bird()
{
	this->initTexture();
}

Bird::Bird(float x, float y)
{
	this->initHitbox();
	this->initTexture();
	this->initSprite();
	this->initAnimation();

	this->bird.setPosition(x, y);
	this->birdX = x;
}

Bird::~Bird()
{
}

const sf::Vector2f Bird::getPosition() const
{
	return this->bird.getPosition();
}

const sf::FloatRect Bird::getGlobalbounds() const
{
	return this->bird.getGlobalBounds();
}

void Bird::setPosition(float x, float y) const
{
	return this->bird,setPosition(x, y);
}

const sf::FloatRect Bird::getGlobalBoundsHitbox() const
{
	return this->birdHitbox.getGlobalBounds();
}

void Bird::update()
{
	this->updateHitbox();
	this->updateAnimation();
	this->updateMovement();
}

void Bird::render(sf::RenderTarget& target)
{
	target.draw(this->bird);
	//target.draw(this->birdHitbox);
}
