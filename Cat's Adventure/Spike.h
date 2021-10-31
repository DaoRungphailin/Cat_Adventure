#pragma once

#include "stdafx.h"

class Spike
{
private:
	sf::Sprite spike;
	sf::Texture spikeTex;

	float spikeX;

	void initSprite();
	void initTexture();

public:
	virtual ~Spike();
	Spike(float x, float y);
	const sf::Vector2f getPosition();
	const sf::FloatRect getGlobalbounds();
	void setPosition(float x, float y);

	void update();
	void render(sf::RenderTarget& target);
};

