#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	if(!this->font.loadFromFile("Fonts/rainyhearts.ttf"))
		std::cout << "ERROR::PLAYERGUI::Could not load the Font sheet!" << "\n";
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
	this->scoreText.setFillColor(sf::Color::Black); //(255, 235, 59, 500)
	this->scoreText.setCharacterSize(40.f);
	this->scoreText.setPosition(800.f, 10.f);
}

PlayerGUI::PlayerGUI()
{
	this->initFont();
	this->initHpBar();
	this->initScoreBar();

	this->hp;
	this->score;
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
	if(this->hp >= 5)
		this->hp += n;
}

void PlayerGUI::updateHpBar()
{
	this->hpBarInner.setSize(sf::Vector2f(this->hp * 3, this->hpBarInner.getSize().y));

	this->hpBarString = std::to_string(this->hp) + " / " + std::to_string(100);
	this->hpBarText.setString(this->hpBarString);
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

void PlayerGUI::render(sf::RenderTarget & target)
{
	this->renderHpBar(target);
	this->renderScore(target);
}
