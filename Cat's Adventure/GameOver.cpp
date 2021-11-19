#include "stdafx.h"
#include "GameOver.h"

void GameOver::initFont()
{
	if (!this->font.loadFromFile("Fonts/rainyhearts.ttf"))
		std::cout << "ERROR::PLAYERGUI::Could not load the Font sheet!" << "\n";
}

void GameOver::initGameOver()
{
	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(sf::Color::Red); //(255, 235, 59, 500)
	this->gameOverText.setCharacterSize(60.f);
	this->gameOverText.setPosition(1500.f, 10.f);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(1700.f / 2.f - this->gameOverText.getGlobalBounds().width / 2.f, 760.f / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
}

GameOver::GameOver()
{
	this->initFont();
	this->initGameOver();
}

GameOver::~GameOver()
{
}

void GameOver::update()
{
}

void GameOver::renderGameOver(sf::RenderTarget& target)
{
	target.draw(this->gameOverText);
}

void GameOver::render(sf::RenderTarget& target)
{
	this->renderGameOver(target);
}
