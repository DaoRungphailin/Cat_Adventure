#pragma once
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;

	void initTexture();
	void initSprite();

	//Animation

	//Movement

	//Core

public:
	Player();
	virtual ~Player();

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

