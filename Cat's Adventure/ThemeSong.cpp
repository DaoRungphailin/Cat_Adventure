#include "stdafx.h"
#include "themesong.h"

themesong::themesong()
{
	buffer.loadFromFile("Sound/03 - Super Mario Bros 2 Main Theme.wav");
	sound.setBuffer(buffer);
	sound.setVolume(1);
}

themesong::~themesong()
{
}

void themesong::Play()
{
	if (sound.getStatus() != sf::Music::Status::Playing) {
		sound.play();
	}
}