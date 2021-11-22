#pragma once
#include "stdafx.h"

class PlayerGUI
{
private:
	
	sf::Font font;
	sf::Font font2;

	//Score Bar
	std::string scoreString;
	sf::Text scoreText;

	//HP Bar
	std::string hpBarString;
	sf::Text hpBarText;
	float hpBarMaxWidth;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;

	//Level
	std::string levelString;
	sf::Text levelText;

	void initFont();
	void initHpBar();
	void initScoreBar();
	void initLevel();

public:
	PlayerGUI();
	virtual ~PlayerGUI();

	int  hp = 100;
	int score = 0;
	int level = 1;

	//Function
	void setScore(int n);
	void setHp(int n);
	void updateScore();
	void updateHpBar();
	void updateLevel();
	void update();

	void renderLevel(sf::RenderTarget& target);
	void renderScore(sf::RenderTarget& target);
	void renderHpBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

