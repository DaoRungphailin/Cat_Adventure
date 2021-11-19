#include "stdafx.h"
#include "Menu.h"

void Menu::initFont()
{
	if (!this->font.loadFromFile("Fonts/Cattino-OVEMo.otf"))
	{
		std::cout << "ERROR::MENU::Could not load the Font sheet!" << "\n";
	}
}

void Menu::initBackground()
{
	if (!this->menuTex.loadFromFile("Backgrounds/CatHand.png"))
	{
		std::cout << "ERROR" << "\n";
	}
	this->menuSprite.setTexture(menuTex);
	this->menuSprite.setScale(1.4f, 1.4f);
}

Menu::Menu(float width, float height)
{
	this->initBackground();
	this->initFont();

	/*Init Menu*/
	menu[0].setFont(font);
	menu[0].setCharacterSize(110);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 1 -100));

	menu[1].setFont(font);
	menu[1].setCharacterSize(80);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("LeaderBoard");
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 2 - 120));

	menu[2].setFont(font);
	menu[2].setCharacterSize(80);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 3 - 180));
}

Menu::~Menu()
{
}

int Menu::getPressedItem()
{
	return selectedItem;
}

void Menu::moveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (selectedItem < MAX_ITEMS - 1)
	{
		printf("%d", this->selectedItem);
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}

void Menu::render(sf::RenderWindow& window)
{
	window.draw(menuSprite);
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}
