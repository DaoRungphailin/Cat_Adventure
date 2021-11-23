#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Coin.h"
#include "Spike.h"
#include "PlayerGUI.h"
#include "HeartItem.h"
#include "Shield.h"
#include "Bomb.h"
#include "Menu.h"
#include "GameOver.h"
#include "Score.h"
#include "Magnet.h"
#include "Bird.h"
#include "Bonus.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;

	//Private function
	void initBird();
	void initMenuPress();
	void initSound();
	void initWindow();
	void initPlayer();
	void initWorld();
	void initHpBar();
	void initGUI();
	void initMenu();
	void initGameOver();
	void initUsername();

	//ITEM
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

	/*Gift*/
	std::vector<Bonus*> gift;
	sf::Clock randomGift;
	sf::Clock delayGift;
	sf::Clock bonusTime;
	float giftX = 0;
	float giftY = 0;
	int countGift = 0;
	bool bonus = false;

	//Coin
	std::vector<Coin*> coin;
	sf::Clock randomCoin;
	float coinX = 0;
	float coinY = 0;
	int countCoin = 0;

	//ENEMIES
	//Spike
	std::vector<Spike*> spike;
	sf::Clock delayCrash;
	int countSpike = 0;
	float spikeX = 0;

	//Bomb
	std::vector<Bomb*> bomb;
	sf::Clock randomBomb;
	sf::Clock delayBomb;
	float bombX = 0;
	float bombY = 0;
	int countBomb = 0;
	int addBomb = 0;

	//Bird
	Bird* bird;
	std::vector<Bird*> birds;
	sf::Clock delayBird;
	int countBird = 0;
	float birdX;
	float birdY;

	//GUI
	PlayerGUI* playerGUI;
	PlayerGUI* hpBar;

	//Game Over
	GameOver* gameOver;
	bool gameOverCheck = false;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;
	float backgroundX = 0;

	//Main Menu
	Menu* menu;
	bool IsOpen = false;
	bool scoreCheck = false;
	bool menuCheck = true;
	sf::Font font2;

	//High Score
	Score scoreBoard;
	std::string name;
	std::string user_name;
	sf::Text US_name;
	sf::Clock timeText;
	float timeUS;
	int end;

	//Username
	sf::Texture nameBackgroundTex;
	sf::Sprite nameBackground;
	sf::Texture nameboardTex;
	sf::Sprite nameboardSprite;
	std::string player_name = "";
	std::vector<char> username;
	bool namestate = false;
	sf::RectangleShape textBox;

	//Press to go to Menu
	std::string menuPress;
	sf::Text menuPressText;
	sf::Text backMenu;

	//Sound
	sf::SoundBuffer buffer[4];
	sf::Sound sound[4];
	bool ThemeSongOn = false;
	bool GameOverSong = false;
	bool LevelUp = false;
	bool TitleSong = false;

public:

	//Functions
	Game();
	virtual ~Game();
	void run();

	void cheat();

	//Functions
	void updateGift();
	void updateBird();
	void updateLevel();
	void updateSound();
	void updateHighScore();
	void updateShield();
	void updateHeartItem();
	void updateHpBar();
	void updateSpike();
	void updateBomb();
	void updateCoin();
	void updatePlayer();
	void updateCollision();
	void updateWorld();
	void update();

	void renderGift();
	void renderBird();
	void renderMenuPress();
	void renderUsername();
	void getName(std::string name);
	void renderHighScore();
	void renderShield();
	void renderHeartItem();
	void renderGUI();
	void renderSpike();
	void renderBomb();
	void renderCoin();
	void rederPlayer();
	void renderWorld();
	void renderMenu();
	void renderNameBg();
	void renderGameOver();
	void render();
	const sf::RenderWindow& getWindow() const;
};

