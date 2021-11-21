#include "stdafx.h"
#include "Game.h"


void Game::initMenuPress()
{
	this->font2.loadFromFile("Fonts/rainyhearts.ttf");
	this->menuPressText.setFont(this->font2);
	this->menuPressText.setFillColor(sf::Color::Black); //(255, 235, 59, 500)
	this->menuPressText.setCharacterSize(50.f);
	this->menuPressText.setString("Press \"Space Bar\" to exit to mainmenu");
	this->menuPressText.setPosition(1700.f / 2.f - this->menuPressText.getGlobalBounds().width / 2.f, 760.f / 2.f - this->menuPressText.getGlobalBounds().height / 2.f + 310.f);
}

void Game::initSound()
{
	buffer[0].loadFromFile("Sound/03 - Super Mario Bros 2 Main Theme.wav");
	sound[0].setBuffer(buffer[0]);

	buffer[1].loadFromFile("Sound/16 - Game Over.wav");
	sound[1].setBuffer(buffer[1]);
}

void Game::initWindow()
{
	this->window.create(sf::VideoMode(1700.f, 760.f), "Cat's Adventure", sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings());
	this->window.setFramerateLimit(60);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/BG1.png"))
	{
		std::cout << "ERORR Can't load background" << "\n";
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initHpBar()
{
	this->hpBar = new PlayerGUI();
}

void Game::initGUI()
{
	this->playerGUI = new PlayerGUI();
}

void Game::initMenu()
{
	this->menu = new Menu(window.getSize().x, window.getSize().y);
}

void Game::initGameOver()
{
	this->gameOver = new GameOver();
}

void Game::initUsername()
{
	if (!this->nameBackgroundTex.loadFromFile("Backgrounds/bgg.jpg"))
	{
		std::cout << "ERORR Can't load background" << "\n";
	}
	this->nameBackground.setTexture(this->nameBackgroundTex);
	//this->nameBackground.setScale(3.f, 3.f);
}

Game::Game()
{
	timeUS = timeText.getElapsedTime().asMilliseconds();
	end = 0;

	this->initMenuPress();
	this->initWindow();
	this->initSound();
	this->initUsername();
	this->initPlayer();
	this->initWorld();
	this->initMenu();
	this->initGUI();
	this->initHpBar();
	this->initGameOver();
}

Game::~Game()
{
	//Player
	delete this->player;

	//Coin
	for (auto* i : this->coin)
	{ 
		delete i;
	}

	//Spike
	for (auto* i : this->spike)
	{
		delete i;
	}

	//Bomb
	for (auto* i : this->bomb)
	{
		delete i;
	}

	//Boost Hp
	for (auto* i : this->heartItem)
	{
		delete i;
	}

	//Shield
	for (auto* i : this->shield)
	{
		delete i;
	}
}

void Game::updateShield()
{
	//Count Shield
	if (this->playerGUI->score % 150 == 0)
	{
		if (countShield < 1)
		{
			shieldX = 70 + rand() % 1500;
			shieldY = 100 + rand() % 450;
			this->shield.push_back(new Shield(shieldX,shieldY));
			this->randomShield.restart();
			countShield++;
		}
	}

	//Update
	for (int i = 0; i < this->shield.size(); ++i)
	{
		this->shield[i]->update();
	}

	//Collision
	for (size_t i = 0; i < this->shield.size(); i++)
	{
		if (this->player->getGlobalBoundsHitbox().intersects(this->shield[i]->getGlobalBoundsHitbox())
			&& this->delayShield.getElapsedTime().asSeconds() > 0.5f && this->playerGUI->hp >= 0)
		{
			//Do not decrease Hp
			this->playerGUI->setHp(0);
			IsAura = true;
			IsStart = true;

			//Delete Shield
			this->shield.erase(this->shield.begin() + i);
			countShield--;
			
			this->delayShield.restart();
			this->delayAura.restart();
			break;

		}
		/*else
		{
			IsAura = false;
			IsStart = false;
		}*/

		//Left of screen
		if (this->shield[i]->getPosition().x + this->shield[i]->getGlobalbounds().width < 0)
		{
			this->shield.erase(this->shield.begin() + i);
			countShield--;
			break;
		}

		//Draw Aura 
		if (IsAura == true)
		{
			this->shield[i]->setPositionAura(this->player->getPosition().x - 40.f, this->player->getPosition().y + 25.f);
		}

		if (delayAura.getElapsedTime().asSeconds() >= 5.f)
			IsAura = false;

	}
}

void Game::updateHeartItem()
{
	//Count Heart
	if (this->playerGUI->score % 100 == 0)
	{
		if (countHeart < 1)
		{
			heartX = 60 + rand() % 1500;
			heartY = 100 + rand() % 500;
			this->heartItem.push_back(new HeartItem(heartX, heartY));
			countHeart++;
		}
	}

	//Update
	for (int i = 0; i < this->heartItem.size(); ++i)
	{
		this->heartItem[i]->update();
	}

	//Collision
	for (size_t i = 0; i < heartItem.size(); i++)
	{
		if (this->player->getGlobalBoundsHitbox().intersects(this->heartItem[i]->getGlobalbounds()) 
			&& this->delayHeart.getElapsedTime().asSeconds() > 0.5f && this->playerGUI->hp <= 80)
		{
			//Boost Hp
			this->playerGUI->setHp(20);

			//Delete heart
			this->heartItem.erase(this->heartItem.begin() + i);
			countHeart--;
			break;

			this->delayHeart.restart();
		}

		//Left of screen
		if (this->heartItem[i]->getPosition().x + this->heartItem[i]->getGlobalbounds().width < 0)
		{
			this->heartItem.erase(this->heartItem.begin() + i);
			countHeart--;
			break;
		}
	}
}

void Game::updateHpBar()
{
	this->playerGUI->update();
}

void Game::updateSpike()
{
	//Count Spike
	if(countSpike < 10)
	{
		spikeX += 500.f;
		this->spike.push_back(new Spike(spikeX, 610));
	}

	//Update
	for (int i = 0; i < this->spike.size(); ++i)
	{
		this->spike[i]->update();
	}

	//Collision
	for (size_t i = 0; i < spike.size(); i++)
	{
		if (this->player->getGlobalBoundsHitbox().intersects(this->spike[i]->getGlobalBoundsHitbox()) 
			&& this->delayCrash.getElapsedTime().asSeconds() >= 0.6f && this->playerGUI->hp >= 10
			&& this->delayAura.getElapsedTime().asSeconds() >= 5.f
			/* && IsStart == true */)
		{
				this->playerGUI->setHp(-10);
				this->delayCrash.restart();
		}

		//Left of screen
		if (this->spike[i]->getPosition().x + this->spike[i]->getGlobalbounds().width < 0)
		{
			this->spike.erase(this->spike.begin() + i);
			countSpike--;
			break;
		}
	}

}

void Game::updateBomb()
{
	//Count Bomb
	if (this->playerGUI->score >= 200)
	{
		if (countBomb < addBomb)
		{
			bombX = 60 + rand() % 1500;
			bombY = rand() % 500;
			this->bomb.push_back(new Bomb(bombX, bombY));
			this->randomBomb.restart();
			countBomb++;
		}

		//Add Bomb 
		if (this->playerGUI->score % 200 == 0 && addBomb <= 3)
		{
			addBomb++;
		}
	}

	//Update
	for (int i = 0; i < this->bomb.size(); ++i)
	{
		this->bomb[i]->update();
	}

	//Collision
	for (size_t i = 0; i < bomb.size(); i++)
	{
		if (this->player->getGlobalBoundsHitbox().intersects(this->bomb[i]->getGlobalbounds())
			&& this->delayBomb.getElapsedTime().asSeconds() > 0.5f)
		{
			//Decrease Hp
			this->playerGUI->setHp(-10);

			//Delete heart
			this->bomb.erase(this->bomb.begin() + i);
			countBomb--;
			break;

			this->delayBomb.restart();
		}

		//Left of screen
		if (this->bomb[i]->getPosition().x + this->bomb[i]->getGlobalbounds().width < 0)
		{
			this->bomb.erase(this->bomb.begin() + i);	
			countBomb--;
			break;
		}
	}
}

void Game::updateCoin()
{
	//Random Coin
	if (this->randomCoin.getElapsedTime().asSeconds() >= 0.5f)
	{
		if (countCoin < 12)
		{
			coinX = rand() % 1700;
			coinY = rand() % 500;
			this->coin.push_back(new Coin(coinX, coinY));
			this->randomCoin.restart();
			countCoin++;
		}
	}

	//Update
	for (int i = 0; i < this->coin.size(); ++i)
	{
		this->coin[i]->update();
	}

	//Collision
	for (size_t i = 0; i < coin.size() ; i++)
	{
		if (this->player->getGlobalBoundsHitbox().intersects(this->coin[i]->getGlobalBoundsHitbox()))
		{
			this->coin.erase(this->coin.begin() + i);
			this->playerGUI->setScore(10);
			countCoin--;
			break;
		}

	//Left of Screen
		if (this->coin[i]->getPosition().x + this->coin[i]->getGlobalbounds().width  < 0)
		{
			this->coin.erase(this->coin.begin() + i);
			countCoin--;
			break;
		}
	}
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateCollision()
{
	//Collision bottom of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height - 110.f > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->jumping = false;
		this->player->jumpingUp = false;
		this->player->gravityBool = false;
		this->player->setPosition(this->player->getPosition().x, this->window.getSize().y - this->player->getGlobalBounds().height - 110.f);
	}
}

void Game::updateWorld()
{
	this->worldBackground.setPosition(backgroundX, this->worldBackground.getPosition().y);
	this->backgroundX -= 0.5;
}

void Game::updateHighScore()
{
	if (scoreCheck == true)
	{
		this->renderHighScore();
	}
}

void Game::updateSound()
{
	if (gameOverCheck == false && ThemeSongOn == false)
	{
		ThemeSongOn = true;
		sound[0].play();
		sound[0].setVolume(1.5);
	}

	if (gameOverCheck == true && GameOverSong == true)
	{
		printf("gameOver sound\n");
		GameOverSong = false;
		sound[0].stop();
		sound[1].play();
		sound[1].setVolume(1.5);
	}
}

void Game::update()
{
	//Polling window events
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)//if Keypressed & key set to Escape
			this->window.close();

		if (this->ev.type == sf::Event::KeyReleased &&
			(
				this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::S
				)
			)
		{
			this->player->resetAnimationTimer();
		}

		//Game Over
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			menuCheck = true;
			IsOpen = false;
		}

		//Set Menu
		if (menuCheck == true)
		{
			switch (ev.type)
			{
			case sf::Event::KeyReleased:
				switch (ev.key.code)
				{
				case sf::Keyboard::Up:
					this->menu->moveUp();
					break;

				case sf::Keyboard::Down:
					this->menu->moveDown();
					break;

				case sf::Keyboard::Return:

					switch (menu->getPressedItem())
					{
					case 0:
						//go to state Play
						namestate = true;
						menuCheck = false;
						scoreCheck = false;
						break;

					case 1:
						//go to state LeaderBoard
						//printf("Leader has been pressed\n");
						scoreCheck = true;
						menuCheck = false;
						namestate = false;
						break;

					case 2:
						//go to state Exit
						window.close();
						break;
					}
				}
				break;

			}
		}
	}

		if (IsOpen == true && playerGUI->hp > 0)
		{
			this->updatePlayer();
			this->updateCollision();
			this->updateWorld();
			this->updateCoin();
			this->updateSpike();
			this->updateHpBar();
			this->updateHeartItem();
			this->updateShield();
			this->updateBomb();
		}
			this->updateSound();
}

	void Game::renderSpike()
	{
		
		for (auto* i : this->spike)
		{
			i->render(this->window);
		}
	}

	void Game::renderShield()
	{
		for (auto* i : this->shield)
		{
			i->render(this->window);

			if (IsAura == true)
				i->renderAura(this->window);
		}
	}

	void Game::renderHeartItem()
	{
		for (auto* i : this->heartItem)
		{
			i->render(this->window);
		}
	}

	void Game::renderGUI()
	{
		this->playerGUI->render(this->window);
	}

	void Game::renderCoin()
	{
		for (auto* i : this->coin)
		{
			i->render(this->window);
		}
	}

	void Game::renderBomb()
	{
		for (auto* i : this->bomb)
		{
			i->render(this->window);
		}
	}

	void Game::renderHighScore()
	{
		this->scoreBoard.Drawscore(this->window);
	}

	void Game::getName(std::string name)
	{

		this->scoreBoard.Pname = name;
	}

	void Game::renderUsername()
	{
		std::stringstream ss;
		player_name = "";
		sf::Text p_name;
		sf::Font font;
		font.loadFromFile("Fonts/Meows-VGWjy.ttf");
		sf::Text enter("Player name", font, 90);
		enter.setFillColor(sf::Color::Black);
		enter.setPosition(600, 200);
		p_name.setFont(font);
		for (int i = 0; i < username.size(); i++)
		{
			player_name += username[i];
		}
		p_name.setCharacterSize(55);
		if (username.empty())
		{
			p_name.setFillColor(sf::Color::Black);
			p_name.setString("_");
		}
		else
		{
			ss << player_name << "_";
			std::string str = ss.str();
			p_name.setString(str);
			p_name.setFillColor(sf::Color::Black);
		}
		p_name.setPosition(820 - (p_name.getGlobalBounds().width / 2), 330);

		window.draw(p_name);
		window.draw(enter);
		this->renderMenuPress();
		//Enter to continue
		this->menuPressText.setString("Press \"Enter\" to continue");
		this->menuPressText.setPosition(1700.f / 2.f - this->menuPressText.getGlobalBounds().width / 2.f, 760.f / 2.f - this->menuPressText.getGlobalBounds().height / 2.f + 310.f);
	}

	void Game::renderMenuPress()
	{
		this->window.draw(menuPressText);
	}

	void Game::renderNameBg()
	{
		this->window.draw(this->nameBackground);
	}

	void Game::rederPlayer()
	{
		this->player->render(this->window);//render players and send to window
	}

	void Game::renderWorld()
	{
		this->window.draw(this->worldBackground);
	}


	void Game::render()
	{
		this->window.clear();

		timeUS = timeText.getElapsedTime().asMilliseconds();

		if (namestate) {


			if (ev.type == sf::Event::TextEntered && timeUS > 500) {

				timeText.restart();
				username.push_back(ev.text.unicode);
			}
			if (!username.empty() && username.back() == 8)
			{
				username.pop_back();
				if (!username.empty())
					username.pop_back();
			}
			if (username.size() != 1 && !username.empty() && username.back() == 13)
			{
				username.pop_back();
			}
			if (!username.empty() && !((username.back() >= 'A' && username.back() <= 'Z') || (username.back() >= 'a' && username.back() <= 'z') || (username.back() >= '0' && username.back() <= '9') || username.back() == '_'))
			{
				username.pop_back();
			}
			if (username.size() > 15)
			{
				username.pop_back();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && username.size() != 0)
			{

				this->getName(player_name);
				namestate = false;
				IsOpen = true;
				std::cout << player_name;
			}

		}

		if (IsOpen == true)
		{
			//Draw World
			this->renderMenu();
			this->renderWorld();

			//Render Coin
			this->renderCoin();

			//Render Spike
			this->renderSpike();

			//Render Bomb
			this->renderBomb();

			//Render HpBar
			this->renderGUI();

			//Render Item
			this->renderHeartItem();
			this->renderShield();

			//Render game
			this->rederPlayer();

			if (this->playerGUI->hp <= 0)
				IsOpen = false;
			
		}
		else
		{
			//Game over screen
			if (this->playerGUI->hp <= 0)
			{
				//Saving Score
				this->scoreBoard.scoreplayer = playerGUI->score;

				if (end < 1)
				{
					this->scoreBoard.wFile();
					end++;

					//GameOver check
					gameOverCheck = true;
					GameOverSong = true;
				}
				//render GameOver
				this->renderGameOver();
			}

			if(menuCheck == true)
			this->renderMenu();

			else
			{
				if (namestate)
				{
					this->renderNameBg();
					this->renderUsername();
					this->renderMenuPress();
				}

				if (scoreCheck == true)
				{
					this->scoreBoard.renderScoreBackground(window);
					this->renderHighScore();
					this->renderMenuPress();
				}
			}
		}

		this->window.display();
	}


const sf::RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}


void Game::renderMenu()
{
	this->menu->render(window);
}


void Game::renderGameOver()
{
	this->gameOver->render(window);
}



