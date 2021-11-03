#pragma once

class PlayerGUI
{
private:
	
	sf::Font font;
	float hpBarMaxWidth;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;

	void initFont();
	void initHpBar();

public:
	PlayerGUI();
	virtual ~PlayerGUI();

	int  hp = 100;
	int score = 0;

	//Function
	void setScore(int n);
	void setHp(int n);
	void updateHpBar();
	void update();

	void renderHpBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

