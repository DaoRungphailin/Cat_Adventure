#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include"stdafx.h"
#include"score.h"

class Score
{

private:
	sf::Font font;
	sf::Font font2;
	sf::Text main, scoretext[5];
	FILE* fp;
	sf::Text top[5];
	int i;
	char temp[255];
	size_t score[6];
	std::string name[6];
	std::vector<std::pair<int, std::string>> userScore;

	size_t getscore;
	std::string getName;


public:

	Score();
	~Score();
	void ReadFile();
	void wFile();
	std::string Pname;
	int scoreplayer;
	void setscoretext();
	void Drawscore(sf::RenderWindow& window);

};