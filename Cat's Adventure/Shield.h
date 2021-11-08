#pragma once
class Shield
{
private:
	sf::Sprite shield;
	sf::Texture shieldTex;
	float heartX;

	//Hitbox
	sf::RectangleShape heartHitbox;

	void initHitbox();
	void initSprite();
	void initTexture();

	void updateHitbox();
	void updateMovement();

public:
	virtual ~Shield();

	HeartItem(float x, float y);

	const sf::Vector2f getPosition();
	const sf::FloatRect getGlobalbounds() const;
	void setPosition(float x, float y);

	//Hitbox
	const sf::FloatRect getGlobalBoundsHitbox() const;

	void update();
	void render(sf::RenderTarget& target);

};

