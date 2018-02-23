#include "menu.h"

Menu_t::Menu_t()
{
	MinPositionX = STANDART_MinPositionX;
	MinPositionY = STANDART_MinPositionY;
	MaxPositionX = STANDART_MaxPositionX;
	MaxPositionY = STANDART_MaxPositionY;
	font1.loadFromFile("font/CyrilicOld.TTF");
	rocket.loadFromFile("textures/rocket.png");
	bomb.loadFromFile("textures/bomb.png");
	explosion.loadFromFile("textures/explosion.png");
}

void Menu_t::start()
{
	sf::RenderWindow window(sf::VideoMode(MaxPositionX, MaxPositionY), "BOMBSvsROCKET!");
	window.setVerticalSyncEnabled(true);
	Key_t Keyboard;
	unsigned position = 1;
	Game_t game;
	while (window.isOpen())
	{
		Processe(window, Keyboard);
		if (Keyboard.up && position > 1)
			position--;
		else if (Keyboard.down && position < 3)
			position++;
		if (Keyboard.enter)
		{
			switch (position)
			{
			case 1:
				game.startGame(window);
				break;
			case 2:
				drawInfo(window);
				break;
			case 3:
				window.close();
				return;
				break;
			default:
				break;
			}
		}
		if (Keyboard.escape)
		{
			window.close();
			return;
		}
		window.clear();
		drawStyle(window);
		drawText(window, "ÐÀÊÅÒÛ ÏÐÎÒÈÂ ÁÎÌÁ!!!", 28, -1, -80);
		drawText(window, "1) Íà÷àòü èãðó", 25, 1);
		drawText(window, "2) Óïðàâëåíèå", 25, 2);
		drawText(window, "3) Âûõîä", 25, 3);
		drawPoint(window, position);
		window.display();
	}
}

void Menu_t::drawText(sf::RenderWindow &window, const std::string &str, unsigned size, int position, int shift)
{
	sf::Text text(str, font1, size);
	text.setPosition((float)(100 + shift), (float)(100 + 50 * position));
	window.draw(text);
}

void Menu_t::drawPoint(sf::RenderWindow &window, unsigned position)
{
	sf::Sprite rocketF;
	rocketF.setTexture(rocket);
	rocketF.setRotation(-90);
	rocketF.setScale((float)0.2, (float)0.2);
	rocketF.setPosition((float)300, (float)(145 + 50 * position));
	window.draw(rocketF);
}

void Menu_t::drawInfo(sf::RenderWindow &window)
{
	Key_t Keyboard;
	while (window.isOpen())
	{
		Processe(window, Keyboard);
		window.clear();
		drawText(window, "ÓÏÐÀÂËÅÍÈÅ:", 45, -1, -55);
		drawText(window, "1) Ïåðåìåùåíèå:", 25, 1, -70);
		drawText(window, "A-D è Left-Right", 25, 2, -20);
		drawText(window, "2) Ñòðåëüáà: ", 25, 3, -70);
		drawText(window, "W è Up", 25, 4, -20);
		drawText(window, "3) Ïàóçà: ", 25, 5, -70);
		drawText(window, "P", 25, 6, -20);
		drawText(window, "4) Âûõîä: ", 25, 7, -70);
		drawText(window, "Escape", 25, 8, -20);
		window.display();
		if (Keyboard.escape)
			return;
	}
}

void Menu_t::drawStyle(sf::RenderWindow &window)
{
	sf::Sprite explosionF;
	explosionF.setTexture(explosion);
	explosionF.setScale((float)0.6, (float)0.6);
	explosionF.setPosition((float)15, (float)270);
	window.draw(explosionF);
}