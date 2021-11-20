#pragma once
#include "stdafx.h"
class GameOver
{
private:

	sf::Font font;
	sf::Font font2;

	//Game Over
	std::string gameOverString;
	sf::Text gameOverText;
	sf::RectangleShape gameOverBox;

	//Press to go to Menu
	std::string menuPress;
	sf::Text menuPressText;

	void initFont();
	void initGameOver();
	void initMenuPress();

public:
	GameOver();
	virtual ~GameOver();

	//Function
	void update();

	void renderMenuPress(sf::RenderTarget& target);
	void renderGameOver(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

