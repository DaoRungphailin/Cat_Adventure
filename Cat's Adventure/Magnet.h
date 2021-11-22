#pragma once
#include "stdafx.h"
class Magnet
{
private:
	sf::Sprite magnet;
	sf::Texture magnetTex;
	float magnetX;

	//Hitbox
	sf::RectangleShape magnetHitbox;

	void initHitbox();
	void initSprite();
	void initTexture();

	void updateHitbox();
	void updateMovement();

public:
	virtual ~Magnet();

	Magnet(float x, float y);

	const sf::Vector2f getPosition();
	const sf::FloatRect getGlobalbounds() const;
	void setPosition(float x, float y);

	//Hitbox
	const sf::FloatRect getGlobalBoundsHitbox() const;

	void update();
	void render(sf::RenderTarget& target);
};

