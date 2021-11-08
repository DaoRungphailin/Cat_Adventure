#include "stdafx.h"
#include "Game.h"


void Game::initWindow()
{
	this->window.create(sf::VideoMode(1000.f, 760.f), "Cat's Adventure", sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings());
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

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initWorld();
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
		this->spike.push_back(new Spike(spikeX, 620.f));
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
			&& this->delayCrash.getElapsedTime().asSeconds() >= 0.6f)
		{
				printf("hp = %d\n",this->playerGUI->hp);
				this->playerGUI->setHp(-5);
				this->delayCrash.restart();
		}

		//Left of screen
		if (this->spike[i]->getPosition().x < 0)
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
	if (this->randomTime.getElapsedTime().asSeconds() >= 0.5f)
	{
		if (countCoin < 12)
		{
			coinX = rand() % 900;
			coinY = rand() % 520;
			this->coin.push_back(new Coin(coinX, coinY));
			this->randomTime.restart();
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
		if (this->coin[i]->getPosition().x < 0)
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
		this->player->setPosition(this->player->getPosition().x, this->window.getSize().y - this->player->getGlobalBounds().height-110);
		this->player->jumping = false;
		this->player->jumpingUp = false;
		this->player->gravityBool = false;
	}
}

void Game::updateWorld()
{
	this->worldBackground.setPosition(backgroundX, this->worldBackground.getPosition().y);
	this->backgroundX -= 0.5;
}

void Game::update()
{
	//Polling window events
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if(this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)//if Keypressed & key set to Escape
			this->window.close();

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
	}
	this->updatePlayer();
	this->updateCollision();
	this->updateWorld();
	this->updateCoin();
	this->updateSpike();
	this->updateHpBar();
}

void Game::renderSpike()
{
	for (auto* i : this->spike)
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
	//Draw World
	this->renderWorld();

	//Render game
	this->rederPlayer();

	//Render Coin
	this->renderCoin();

	//Render Spike
	this->renderSpike();

	//Render HpBar
	this->renderGUI();

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}

