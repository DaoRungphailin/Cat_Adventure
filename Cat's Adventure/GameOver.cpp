#include "stdafx.h"
#include "GameOver.h"

void GameOver::initFont()
{
	if (!this->font.loadFromFile("Fonts/3Dventure.ttf"))
		std::cout << "ERROR::PLAYERGUI::Could not load the Font sheet!" << "\n";

	if (!this->font2.loadFromFile("Fonts/rainyhearts.ttf"))
		std::cout << "ERROR::PLAYERGUI::Could not load the Font sheet!" << "\n";
}

void GameOver::initGameOver()
{
	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(sf::Color::Red); //(255, 235, 59, 500)
	this->gameOverText.setCharacterSize(100.f);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(1700.f / 2.f - this->gameOverText.getGlobalBounds().width / 2.f, 760.f / 2.f - this->gameOverText.getGlobalBounds().height / 2.f - 50.f);

	this->gameOverBox.setFillColor(sf::Color::Black);
	this->gameOverBox.setSize(sf::Vector2f(680.f, 150.f));
	this->gameOverBox.setPosition(1700.f / 2.f - this->gameOverText.getGlobalBounds().width / 2.f - 50.f , 760.f / 2.f - this->gameOverText.getGlobalBounds().height / 2.f - 50.f);
}

void GameOver::initMenuPress()
{
	this->menuPressText.setFont(this->font2);
	this->menuPressText.setFillColor(sf::Color::White); //(255, 235, 59, 500)
	this->menuPressText.setCharacterSize(50.f);
	this->menuPressText.setString("Press \"Space Bar\" to exit to mainmenu");
	this->menuPressText.setPosition(1700.f / 2.f - this->menuPressText.getGlobalBounds().width / 2.f, 760.f / 2.f - this->menuPressText.getGlobalBounds().height / 2.f + 200.f);
}

GameOver::GameOver()
{
	this->initFont();
	this->initGameOver();
	this->initMenuPress();
}

GameOver::~GameOver()
{
}

void GameOver::update()
{
}

void GameOver::renderMenuPress(sf::RenderTarget& target)
{
	target.draw(this->menuPressText);
}

void GameOver::renderGameOver(sf::RenderTarget& target)
{
	target.draw(this->gameOverBox);
	target.draw(this->gameOverText);
}

void GameOver::render(sf::RenderTarget& target)
{
	this->renderGameOver(target);
	this->renderMenuPress(target);
}
