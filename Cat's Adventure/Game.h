#pragma once
#include "stdafx.h"
#include "Player.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;
	
	void initWindow();
	void initPlayer();

public:

	//Functions
	Game();
	virtual ~Game();

	//Functions
	void updatePlayer();
	void updateCollision();
	void update();
	void rederPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;
};

