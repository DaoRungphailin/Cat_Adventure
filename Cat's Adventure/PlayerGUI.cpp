#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	if(!this->font.loadFromFile("Fonts/rainyhearts.ttf"))
		std::cout << "ERROR::PLAYERGUI::Could not load the Font sheet!" << "\n";

	if (!this->font2.loadFromFile("Fonts/3Dventure.ttf"))
		std::cout << "ERROR::MENU::Could not load the Font sheet!" << "\n";
}

void PlayerGUI::initHpBar()
{
	float width = 300.f;
	float height = 40.f;
	float x = 20.f;
	float y = 20.f;

	this->hpBarMaxWidth = width;

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setPosition(this->hpBarInner.getPosition().x + 20.f, this->hpBarInner.getPosition().y);
}

void PlayerGUI::initScoreBar()
{
	this->scoreText.setFont(this->font);
	this->scoreText.setFillColor(sf::Color::Black);
	this->scoreText.setCharacterSize(40.f);
	this->scoreText.setPosition(1500.f, 10.f);
}

void PlayerGUI::initLevel()
{
	this->levelText.setFont(this->font2);
	this->levelText.setFillColor(sf::Color::Black);
	this->levelText.setCharacterSize(50.f);
	this->levelText.setPosition(800 - this->levelText.getGlobalBounds().width, 10.f);
}

PlayerGUI::PlayerGUI()
{
	this->initFont();
	this->initHpBar();
	this->initScoreBar();
	this->initLevel();

	this->hp;
	this->score;
	this->level;
}

PlayerGUI::~PlayerGUI()
{
}

//Function
void PlayerGUI::setScore(int n)
{
	this->score += n;
}

void PlayerGUI::setHp(int n)
{
	if(this->hp >= 0)
		this->hp += n;
}

void PlayerGUI::updateHpBar()
{
	this->hpBarInner.setSize(sf::Vector2f(this->hp * 3, this->hpBarInner.getSize().y));

	this->hpBarString = std::to_string(this->hp) + " / " + std::to_string(100);
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::updateLevel()
{
	this->levelString = "Level " + std::to_string(this->level);
	this->levelText.setString(this->levelString);
}

void PlayerGUI::updateScore()
{
	this->scoreString = "score : " + std::to_string(this->score);
	this->scoreText.setString(this->scoreString);
}

void PlayerGUI::update()
{
	this->updateHpBar();
	this->updateScore();
	this->updateLevel();
}

void PlayerGUI::renderLevel(sf::RenderTarget& target)
{
	target.draw(this->levelText);
}

void PlayerGUI::renderScore(sf::RenderTarget& target)
{
	target.draw(this->scoreText);
}

void PlayerGUI::renderHpBar(sf::RenderTarget & target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpBarText);
}


void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderHpBar(target);
	this->renderScore(target);
	this->renderLevel(target);
}
