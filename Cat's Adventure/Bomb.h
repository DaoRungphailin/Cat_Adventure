#pragma once
#include "stdafx.h"

class Bomb
{
private:
	sf::Sprite bomb;
	sf::Texture bombTex;
	float bombX;

	//Hitbox
	sf::RectangleShape bombHitbox;

	void initHitbox();
	void initSprite();
	void initTexture();

	void updateHitbox();
	void updateMovement();

public:
	virtual ~Bomb();

	Bomb(float x, float y);

	const sf::Vector2f getPosition();
	const sf::FloatRect getGlobalbounds() const;
	void setPosition(float x, float y);

	//Hitbox
	const sf::FloatRect getGlobalBoundsHitbox() const;

	void update();
	void render(sf::RenderTarget& target);
};

