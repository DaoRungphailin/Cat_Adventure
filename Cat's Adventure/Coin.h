#pragma once

#include "stdafx.h"

class Coin
{
private:
	sf::Sprite coin;
	sf::Texture coinTex;
	sf::IntRect currentFrame;
	sf::Clock animationTimer;

	float coinX;

	//Hitbox
	sf::RectangleShape coinHitbox;

	void initHitbox();
	void initSprite();
	void initTexture();
	void initAnimation();

	//Update
	void updateHitbox();
	void updateAnimation();
	void updateMovement();

public:
	virtual ~Coin();

	Coin(float x, float y);
	const sf::Vector2f getPosition();
	const sf::FloatRect getGlobalbounds();
	void setPosition(float x, float y);
	
	//Hitbox
	const sf::FloatRect getGlobalBoundsHitbox() const;

	void update();
	void render(sf::RenderTarget& target);
};

