#pragma once
#include "Coin.h"

enum PLAYER_ANIMATION_STATES {IDLE=0,MOVING_LEFT, MOVING_RIGHT,JUMPING,FALLING};

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	sf::Clock timeJumping;

	//Animation
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

	//time
	float delayJump;
	bool changeJump = true;

	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;


	//Core
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

	float movementSpeed;

public:
	Player();
	virtual ~Player();

	//Coin
	

	//Accessors
	const bool& getAnimSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityX();
	void resetVelocityY();

	//Jumping
	bool jumping = false;//if jumping on
	bool jumpingUp = false;//if jumping on and fall down
	bool gravityBool = false; //open-close gravity

	//Functions
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);
};

