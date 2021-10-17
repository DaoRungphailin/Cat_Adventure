#include "stdafx.h"
#include "Game.h"


void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "Cat's Adventure", sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings());
	this->window.setFramerateLimit(144);
}

void Game::initPlayer()
{
	this->player = new Player();
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
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
	if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getGlobalBounds().left,
			this->window.getSize().y - this->player->getGlobalBounds().height
			);
	}
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
}

void Game::rederPlayer()
{
	this->player->render(this->window);//render players and send to window
}

void Game::render()
{
	this->window.clear(sf::Color::Black);

	//Render game
	this->rederPlayer();

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}
