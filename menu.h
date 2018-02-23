#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "game.h"

class Menu_t
{
	int MinPositionX;
	int MinPositionY;
	int MaxPositionX;
	int MaxPositionY;
	sf::Font font1;
	sf::Texture rocket, bomb, explosion;
public:
	Menu_t();
	void start();
private:
	void drawPoint(sf::RenderWindow &window, unsigned position);
	void drawText(sf::RenderWindow &window, const std::string &str, unsigned size, int position, int shift = 0);
	void drawInfo(sf::RenderWindow &window);
	void drawStyle(sf::RenderWindow &window);
};