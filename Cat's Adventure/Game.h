#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Coin.h"
#include "Spike.h"
#include "PlayerGUI.h"

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
	void initHpBar();
	void initGUI();

	//Coin
	std::vector<Coin*> coin;
	sf::Clock randomTime;
	float coinX = 0;
	float coinY = 0;
	int countCoin = 0;

	//Spike
	std::vector<Spike*> spike;
	sf::Clock delayCrash;
	int countSpike = 0;
	float spikeX = 0;

	//GUI
	PlayerGUI* playerGUI;
	PlayerGUI* hpBar;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;
	float backgroundX = 0;

public:

	//Functions
	Game();
	virtual ~Game();

	//Functions
	void updateHpBar();
	void updateSpike();
	void updateCoin();
	void updatePlayer();
	void updateCollision();
	void updateWorld();
	void update();

	void renderHpBar();
	void renderSpike();
	void renderCoin();
	void rederPlayer();
	void renderWorld();
	void render();
	const sf::RenderWindow& getWindow() const;
};

