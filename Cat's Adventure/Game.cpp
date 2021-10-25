#include "stdafx.h"
#include "Game.h"


void Game::initWindow()
{
	this->window.create(sf::VideoMode(1000.f, 760.f), "Cat's Adventure", sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings());
	this->window.setFramerateLimit(144);
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

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initWorld();
}

Game::~Game()
{
	delete this->player;
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

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}
