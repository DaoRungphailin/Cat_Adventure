#pragma once
#include "stdafx.h"

#define MAX_ITEMS 3 //Start, Leaderboard, Exit

class Menu
{
private:

	int selectedItem = 0;
	sf::Font font;
	sf::Text menu[MAX_ITEMS]; 

	sf::Sprite menuSprite;
	sf::Texture menuTex;

	//Name
	sf::RectangleShape MynameBox;
	sf::Font font2;
	sf::Text myName;


	void initFont();
	void initBackground();
	void initName();

public:
	Menu(float width, float height);

	~Menu();
	int getPressedItem();

	//functions
	void moveUp();
	void moveDown();

	void renderMenu(sf::RenderWindow& target);
	void renderName(sf::RenderWindow& target);
	void render(sf::RenderWindow& window);
};

