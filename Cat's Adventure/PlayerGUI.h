#pragma once

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

	//Game Over
	std::string gameOverString;
	sf::Text gameOverText;

	void initFont();
	void initHpBar();
	void initScoreBar();
	void initGameOver();

public:
	PlayerGUI();
	virtual ~PlayerGUI();

	int  hp = 100;
	int score = 0;

	//Function
	void setScore(int n);
	void setHp(int n);
	void updateScore();
	void updateHpBar();
	void update();

	void renderScore(sf::RenderTarget& target);
	void renderHpBar(sf::RenderTarget& target);
	void renderGameOver(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

