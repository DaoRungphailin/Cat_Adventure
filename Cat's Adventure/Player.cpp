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
	this->sprite.setScale(5.f, 5.f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 22.f;
	this->velocityMin = 1.f;
	this->acceleration = 4.f;
	this->drag = 0.87f;
	this->gravity = 4.f;
	this->velocityMaxY = 15.f;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{

}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;
	return anim_switch;
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}



void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	//Acceleration 
	this->velocity.x += dir_x * this->acceleration;

	//Limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.0 * this->gravity;
	if (std::abs(this->velocity.x) > this->velocityMaxY)
	{
		this->velocity.x = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	//Deceleration
	this->velocity *= this->drag;

	//Limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	this->sprite.move(this->velocity);
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
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 96.f;
			this->currentFrame.left = 48.f;
			this->sprite.setTextureRect(this->currentFrame);
		}
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
		this->sprite.setScale(5.f, 5.f);
		this->sprite.setOrigin(0.f, 0.f);
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
		this->sprite.setScale(-5.f, 5.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width /5,0.f);
	}
	else
		this->animationTimer.restart();//stop when not press key
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
