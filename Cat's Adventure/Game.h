#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Coin.h"
#include "Spike.h"
#include "PlayerGUI.h"
#include "HeartItem.h"
#include "Shield.h"
#include "Menu.h"

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
	void initMenu();

	//Item
	/*Boost Hp*/
	std::vector<HeartItem*> heartItem;
	sf::Clock randomHeart;
	sf::Clock delayHeart;
	float heartX = 0;
	float heartY = 0;
	int countHeart = 0;

	/*Shield*/
	std::vector<Shield*> shield;
	sf::Clock randomShield;
	sf::Clock delayShield;
	sf::Clock delayAura;
	bool IsStart = false;
	bool IsAura = false;
	float shieldX = 0;
	float shieldY = 0;
	int countShield = 0;

	//Coin
	std::vector<Coin*> coin;
	sf::Clock randomCoin;
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

	//Game Over
	PlayerGUI* gameOver;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;
	float backgroundX = 0;

	//Main Menu
	Menu* menu;
	bool IsOpen = true;

public:

	//Functions
	Game();
	virtual ~Game();

	void run();

	//Functions
	void updateShield();
	void updateHeartItem();
	void updateHpBar();
	void updateSpike();
	void updateCoin();
	void updatePlayer();
	void updateCollision();
	void updateWorld();
	void updatePollEvent();
	void update();

	void renderShield();
	void renderHeartItem();
	void renderGUI();
	void renderSpike();
	void renderCoin();
	void rederPlayer();
	void renderWorld();
	void renderMenu();
	void renderGameOver();
	void render();
	const sf::RenderWindow& getWindow() const;
};

