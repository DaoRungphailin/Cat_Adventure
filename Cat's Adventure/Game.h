#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Coin.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;

	//Private function
	void initWindow();
	void initPlayer();
	void initWorld();

	//Coin
	std::vector<Coin*> coin;
	sf::Clock randomTime;
	float temp = 0;


	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;
	float backgroundX = 0;

public:

	//Functions
	Game();
	virtual ~Game();

	//Functions
	void updateCoin();
	void updatePlayer();
	void updateCollision();
	void updateWorld();
	void update();

	void renderCoin();
	void rederPlayer();
	void renderWorld();
	void render();
	const sf::RenderWindow& getWindow() const;
};

