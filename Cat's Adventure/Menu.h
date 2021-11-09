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

	void initFont();
	void initBackground();

public:
	Menu(float width, float height);

	~Menu();
	int getPressedItem();

	//functions
	/*void initBackground();*/
	void moveUp();
	void moveDown();

	void render(sf::RenderWindow& window);
};

