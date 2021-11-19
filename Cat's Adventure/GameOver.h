#pragma once
#include "stdafx.h"
class GameOver
{
private:

	sf::Font font;

	//Game Over
	std::string gameOverString;
	sf::Text gameOverText;
	sf::RectangleShape gameOverBox;

	void initFont();
	void initGameOver();

public:
	GameOver();
	virtual ~GameOver();

	//Function
	void update();

	void renderGameOver(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

