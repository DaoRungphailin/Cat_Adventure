#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Textures/many_cat.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 96, 50, 50);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(4.f, 4.f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
}

Player::~Player()
{

}



void Player::updatePhysics()
{

}

void Player::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//Left
	{
		this->sprite.move(-3.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))//Right
	{
		this->sprite.move(3.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
	/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))//Top
	{
		this->sprite.move(0.f, -3.f);
		this->animState = PLAYER_ANIMATION_STATES::JUMPING;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))//Down
	{
		this->sprite.move(0.f, 3.f);
		this->animState = PLAYER_ANIMATION_STATES::FALLING;
	}*/
}

void Player::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
			this->currentFrame.top = 96.f;
			this->currentFrame.left = 48.f;
			this->sprite.setTextureRect(this->currentFrame);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			this->currentFrame.top = 96.f;
			this->currentFrame.left += 48.f;
			if (this->currentFrame.left >= 144.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(4.f, 4.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			this->currentFrame.top = 96.f;
			this->currentFrame.left += 48.f;
			if (this->currentFrame.left >= 144.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-4.f, 4.f);
	}
	else
		this->animationTimer.restart();//stop when not press key
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
