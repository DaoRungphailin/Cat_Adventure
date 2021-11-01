#pragma once

#include "stdafx.h"

class Spike
{
private:
	sf::Sprite spike;
	sf::Texture spikeTex;

	float spikeX;

	//Hitbox
	sf::RectangleShape spikeHitbox;

	void initHitbox();
	void initSprite();
	void initTexture();

public:
	virtual ~Spike();

	Spike(float x, float y);
	const sf::Vector2f getPosition();
	const sf::FloatRect getGlobalbounds();
	void setPosition(float x, float y);

	//Hitbox
	const sf::FloatRect getGlobalBoundsHitbox() const;

	void update();
	void updateHitbox();
	void updateMovement();
	void render(sf::RenderTarget& target);
};

