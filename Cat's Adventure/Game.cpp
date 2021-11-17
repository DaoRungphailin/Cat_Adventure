#include "stdafx.h"
#include "Game.h"


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

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initWorld();
	this->initMenu();
	this->initGUI();
	this->initHpBar();
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
	if (this->randomShield.getElapsedTime().asSeconds() >= 0.5f)
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

		//Left of screen
		if (this->shield[i]->getPosition().x + this->shield[i]->getGlobalbounds().width < 0)
		{
			this->shield.erase(this->shield.begin() + i);
			countShield--;
			break;
		}
	}
}

void Game::updateHeartItem()
{
	//Count Heart
	if (this->randomHeart.getElapsedTime().asSeconds() >= 0.5f)
	{
		if (countHeart < 1)
		{
			heartX = 60 + rand() % 1500;
			heartY = 100 + rand() % 500;
			this->heartItem.push_back(new HeartItem(heartX, heartY));
			this->randomHeart.restart();
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
				printf("hp = %d\n",this->playerGUI->hp);
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
			this->playerGUI->setScore(1);
			countCoin--;
			break;
			//printf("score = %d\n", this->playerGUI->score);
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
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->jumping = false;
		this->player->jumpingUp = false;
		this->player->gravityBool = false;
		this->player->setPosition(this->player->getPosition().x, this->window.getSize().y - this->player->getGlobalBounds().height - 110);
	}
}

void Game::updateWorld()
{
	this->worldBackground.setPosition(backgroundX, this->worldBackground.getPosition().y);
	this->backgroundX -= 0.5;
}

void Game::run()
{
	while (this->window.isOpen())
	{
		this->updatePollEvent();

		if (this->playerGUI->hp > 0)
			this->update();

		this->render();
	}
}

void Game::updatePollEvent()
{
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)//if Keypressed & key set to Escape
			this->window.close();
	}
}

void Game::update()
{
	//Polling window events
	while (this->window.pollEvent(this->ev))
	{
		/*if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)//if Keypressed & key set to Escape
			this->window.close();*/

		if (
			this->ev.type == sf::Event::KeyReleased &&
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

		//Set Menu
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
					printf("Player has been pressed");
					//go to state
					IsOpen = true;
					break;

				case 1:
					//go to state
					printf("Leader has been pressed");
					break;

				case 2:
					window.close();
					break;
				}
			}
			break;

		}
	}

	if (IsOpen == true)
	{

		this->updatePlayer();
		this->updateCollision();
		this->updateWorld();
		this->updateCoin();
		this->updateSpike();
		this->updateHpBar();
		this->updateHeartItem();
		this->updateShield();
	}
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
	for (auto* i:this->coin)
	{
		i->render(this->window);
	}
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

	if (IsOpen == true)
	{

		//Draw World
		this->renderMenu();
		this->renderWorld();

		//Render game
		this->rederPlayer();

		//Render Coin
		this->renderCoin();

		//Render Spike
		this->renderSpike();

		//Render HpBar
		this->renderGUI();

		//Render Item
		this->renderHeartItem();
		this->renderShield();

		//Game over screen
		if (this->playerGUI->hp <= 0)
			this->renderGameOver();

	}
	else
	{
		this->renderMenu();
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

