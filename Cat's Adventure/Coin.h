#pragma once

#include "stdafx.h"

class Coin
{
private:
	sf::Sprite coin;
	sf::Texture coinTex;
	sf::IntRect currentFrame;
	sf::Clock animationTimer;

	void initSprite();
	void initTexture();
	void initAnimation();

public:
	virtual ~Coin();
	Coin(float x, float y);
	const sf::Vector2f getPosition();
	const sf::FloatRect getGlobalbounds();
	void setPosition(float x, float y);

	void update();
	void render(sf::RenderTarget& target);
};

