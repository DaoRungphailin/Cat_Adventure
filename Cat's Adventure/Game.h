#pragma once
#include "stdafx.h"
#include "Player.h"

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

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;
	float backgroundX = 0;

public:

	//Functions
	Game();
	virtual ~Game();

	//Functions
	void updatePlayer();
	void updateCollision();
	void updateWorld();
	void update();

	void rederPlayer();
	void renderWorld();
	void render();
	const sf::RenderWindow& getWindow() const;
};

