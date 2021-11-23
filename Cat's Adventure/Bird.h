#pragma once
#include "stdafx.h"

class Bird
{
private:
	sf::Sprite bird;
	sf::Texture birdTex;
	sf::IntRect currentFrame;
	sf::Clock animationTimer;

	//hitbox
	sf::RectangleShape birdHitbox;

	float birdX;

	void initTexture();
	void initSprite();
	void initAnimation();
	void initHitbox();

	void updateHitbox();
	void updateMovement();
	void updateAnimation();

public:
	Bird();
	Bird(float x, float y);
	virtual ~Bird();

	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalbounds() const;
	void setPosition(float x, float y) const;

	//Hitbox
	const sf::FloatRect getGlobalBoundsHitbox() const;

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

