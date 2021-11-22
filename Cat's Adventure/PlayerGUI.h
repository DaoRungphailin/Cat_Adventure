#pragma once
#include "stdafx.h"

class PlayerGUI
{
private:
	
	sf::Font font;

	//Score Bar
	std::string scoreString;
	sf::Text scoreText;

	//HP Bar
	std::string hpBarString;
	sf::Text hpBarText;
	float hpBarMaxWidth;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;

	void initFont();
	void initHpBar();
	void initScoreBar();

public:
	PlayerGUI();
	virtual ~PlayerGUI();

	int  hp = 100;
	int score = 0;
	int level = 1;

	//Function
	void setScore(int n);
	void setHp(int n);
	void setLevel(int n);
	void updateScore();
	void updateHpBar();
	void update();

	void renderScore(sf::RenderTarget& target);
	void renderHpBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

