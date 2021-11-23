#pragma once
class Bonus
{
private:
	sf::Sprite gift;
	sf::Texture giftTex;
	float giftX;

	//Hitbox
	sf::RectangleShape giftHitbox;

	void initHitbox();
	void initSprite();
	void initTexture();

	void updateHitbox();
	void updateMovement();

public:
	virtual ~Bonus();

	Bonus(float x, float y);

	const sf::Vector2f getPosition();
	const sf::FloatRect getGlobalbounds() const;
	void setPosition(float x, float y);

	//Hitbox
	const sf::FloatRect getGlobalBoundsHitbox() const;

	void update();
	void render(sf::RenderTarget& target);

};

