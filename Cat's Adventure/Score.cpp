#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "score.h"

using namespace std;
void Score::initScoreBackground()
{
	if (!this->scoreBgTex.loadFromFile("Backgrounds/bg.png"))
	{
		std::cout << "ERORR Can't load background" << "\n";
	}
	this->scoreBg.setTexture(this->scoreBgTex);
	this->scoreBg.setScale(1.35f, 1.35f);
}

Score::Score()
{
	this->initScoreBackground();
	font.loadFromFile("Fonts/baby blocks.ttf");
	font2.loadFromFile("Fonts/rainyhearts.ttf");
	sf::Text ttext("SCOREBOARD", font, 80);
	main = ttext;
	main.setFillColor(sf::Color::Black);
	main.setOrigin(sf::Vector2f(main.getGlobalBounds().width / 2, 0));
	main.setPosition(sf::Vector2f(900, 50));
	for (int i = 0; i < 5; i++)
	{
		scoretext[i].setCharacterSize(65);
		scoretext[i].setFillColor(sf::Color::Black);
		scoretext[i].setPosition(900, 200 + (i * 80));
		scoretext[i].setFont(font2);
	}
}

Score::~Score()
{

}

void Score::ReadFile()
{
	fp = fopen("./score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);
		this->userScore.push_back(make_pair(score[i], name[i]));
	}
}

void Score::wFile()
{
	ReadFile();
	this->name[5] = Pname;
	this->score[5] = scoreplayer;
	this->userScore.push_back(make_pair(this->score[5], this->name[5]));
	sort(userScore.begin(), userScore.end());

	fp = fopen("./score.txt", "w");
	for (int i = 5; i > 0; i--)
	{
		strcpy(temp, userScore[i].second.c_str());
		fprintf(fp, "%s %d\n", temp, userScore[i].first);
	}

	for (int i = 0; i < 6; i++)
	{
		userScore.pop_back();
	}
	fclose(this->fp);
}

void Score::setscoretext()
{
}

void Score::renderScoreBackground(sf::RenderWindow& window)
{
	window.draw(this->scoreBg);
}

void Score::Drawscore(sf::RenderWindow& window)
{
	std::stringstream ss[5];
	ReadFile();
	fclose(this->fp);
	for (int i = 0; i < 5; i++) {
		ss[i] << userScore[i].second << "       " << userScore[i].first;
		scoretext[i].setString(ss[i].str());
		scoretext[i].setOrigin(sf::Vector2f(scoretext[i].getGlobalBounds().width / 2, 0));
		window.draw(scoretext[i]);
	}
	while (!userScore.empty())
	{
		userScore.pop_back();
	}

	window.draw(main);
}