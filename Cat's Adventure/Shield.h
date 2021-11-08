#pragma once
class Shield
{
private:
	sf::Sprite shield;
	sf::Texture shieldTex;
	float shieldX;

	//Hitbox
	sf::RectangleShape shieldHitbox;

	void initHitbox();
	void initSprite();
	void initTexture();

	void updateHitbox();
	void updateMovement();

public:
	virtual ~Shield();

	Shield(float x, float y);

	const sf::Vector2f getPosition();
	const sf::FloatRect getGlobalbounds() const;
	void setPosition(float x, float y);

	//Hitbox
	const sf::FloatRect getGlobalBoundsHitbox() const;

	void update();
	void render(sf::RenderTarget& target);

};

