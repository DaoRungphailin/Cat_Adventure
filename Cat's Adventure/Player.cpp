#include "stdafx.h"
#include "Player.h"

void Player::initHitbox()
{
	playerHitbox.setOutlineColor(sf::Color::Green);
	playerHitbox.setOutlineThickness(2.f);
	playerHitbox.setFillColor(sf::Color::Transparent);
	playerHitbox.setSize(sf::Vector2f(135.f, 100.f));
}

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
	this->currentFrame = sf::IntRect(0, 96, 48, 48);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(4.f, 4.f);
	this->sprite.setPosition(100.f, 900.f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->acceleration = 3.f;
	this->drag = 0.9f;
	this->gravity = 0.6f;
	this->velocityMaxY = 1.f;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
	this->initHitbox();

	this->movementSpeed = 14.f;
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

const sf::FloatRect Player::getGlobalBoundsHitbox() const
{
	return this->playerHitbox.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityX()
{
	this->velocity.x = 0.f;
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
	this->sprite.move(this->movementSpeed * dir_x, this->movementSpeed * dir_y);

	//Acceleration 
	this->velocity.x += dir_x * this->acceleration;

	//Limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

void Player::updateHitbox()
{
	playerHitbox.setPosition(sprite.getPosition().x + 25.f, sprite.getPosition().y + 95.f);
}

void Player::updatePhysics()
{
	//Jumping
	if (this->jumping == true && this->gravityBool == false)
	{
		if (this->velocity.y < 0)//peak Vy=0
			this->jumpingUp = false;
		if (this->jumpingUp == true)//jumping
			this->velocity.y -= 1.f;
		else
		{
			//Gravity
			this->velocity.y += (1.0 * this->gravity);
			if (std::abs(this->velocity.x) > this->velocityMaxY)
				this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
		}
	}
	else
		this->velocity.y += (1.0 * this->gravity);
		

	if(this->gravityBool == true)
		this->velocity.y += (1.0 * this->gravity);

	if (this->sprite.getPosition().y + this->sprite.getGlobalBounds().height > 650)
	{
		jumpTimes = 0;
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
	this->delayJump = timeJumping.getElapsedTime().asSeconds();
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//Left
	{
		if (this->getPosition().x > 0)
		{
			this->sprite.move(-3.f, 0.f);
			this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))//Right
	{
		if (this->getPosition().x < 1700.f - this->sprite.getGlobalBounds().width + 30.f)
		{
			this->sprite.move(3.f, 0.f);
			this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))//Top
	{
		if (this->getPosition().y > 0)
		{
			if (delayJump > 0.2f && jumpTimes < 1)
			{
				this->jumping = true;
				this->jumpingUp = true;
				this->gravityBool = true;
				this->velocity.y = -50.f;
				this->timeJumping.restart();
				jumpTimes++;
				//printf("%d\n", jumpTimes);
			}
		}
		//this->animState = PLAYER_ANIMATION_STATES::JUMPING;
		
	}
	/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))//Down
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
			this->currentFrame.left += 48.f;
			if (this->currentFrame.left >= 144.f)
				this->currentFrame.left = 0;
			this->animationTimer.restart();
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
		this->sprite.setScale(4.f, 4.f);
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
		this->sprite.setScale(-4.f, 4.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width /5,0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::JUMPING)
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
		this->sprite.setOrigin(0.f, 0.f);
	}
	else
		this->animationTimer.restart();//stop when not press key
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
	this->updateHitbox();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	//target.draw(this->playerHitbox);
}
