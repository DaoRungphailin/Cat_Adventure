#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	if(!this->font.loadFromFile("Fonts/Moutarde DEMO.otf"))
		std::cout << "ERROR::PLAYERGUI::Could not load the Font sheet!" << "\n";
}

void PlayerGUI::initHpBar()
{
	float width = 300.f;
	float height = 40.f;
	float x = 20.f;
	float y = 20.f;

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarMaxWidth = width;

	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());
}

PlayerGUI::PlayerGUI()
{
	this->initFont();
	this->initHpBar();

	this->hp;
	this->score;
}

PlayerGUI::~PlayerGUI()
{
}

//Function
void PlayerGUI::updateHpBar()
{
	this->hpBarInner.setSize(sf::Vector2f(this->hp * 3, this->hpBarInner.getSize().y));
}

void PlayerGUI::setScore(int n)
{
	this->score += n;
}

void PlayerGUI::setHp(int n)
{
	if(this->hp >= 5)
		this->hp += n;
}

void PlayerGUI::update()
{
	this->updateHpBar();
}

void PlayerGUI::renderHpBar(sf::RenderTarget & target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
}

void PlayerGUI::render(sf::RenderTarget & target)
{
	this->renderHpBar(target);
}
