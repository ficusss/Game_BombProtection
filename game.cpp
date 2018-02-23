#include "game.h"
#include "bullet.h"
#include "bomb.h"
#include "gun.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <sstream>

Game_t::Game_t()
{
	MinPositionX = STANDART_MinPositionX;
	MinPositionY = STANDART_MinPositionY;
	MaxPositionX = STANDART_MaxPositionX;
	MaxPositionY = STANDART_MaxPositionY;
	sf::Texture texture1, texture2, texture3;
	texture1.loadFromFile("textures/rocket.png");
	texture2.loadFromFile("textures/bomb.png");
	texture3.loadFromFile("textures/explosion.png");
	arrTexture.push_back(std::make_shared<sf::Texture>(texture1));
	arrTexture.push_back(std::make_shared<sf::Texture>(texture2));
	arrTexture.push_back(std::make_shared<sf::Texture>(texture3));
	sf::SoundBuffer soundBuff1, soundBuff2;
	mainMusic.openFromFile("sound/main.ogg");
	soundBuff1.loadFromFile("sound/shot.ogg");
	soundBuff2.loadFromFile("sound/explosion.ogg");
	arrSoundBuff.push_back(std::make_shared<sf::SoundBuffer>(soundBuff1));
	arrSoundBuff.push_back(std::make_shared<sf::SoundBuffer>(soundBuff2));	
	soundExplosion.setVolume(25);
	mainMusic.setVolume(30);
	sf::Font font1;
	font1.loadFromFile("font/CyrilicOld.TTF");
	arrFont.push_back(std::make_shared<sf::Font>(font1));
}

void Game_t::update()
{
	arrBomb.clear();
	arrBullet.clear();
	arrExplosion.clear();
	score = 0;
	lvl++;
}

void Game_t::startGame(sf::RenderWindow &window)
{
	lvl = 0;
	endGame = false;
	update();// 1 lvl
	StartBombSpeed = Vector_t(0, 0.04);
	ScaleBomb = Vector_t(0.5, 0.5);
	if (!startLvl(window))			
		return;
	pauseAndText(window, "УРА!!!", "Уровень 1 пройден!");
	update();// 2 lvl
	StartBombSpeed = Vector_t(0, 0.04);
	ScaleBomb = Vector_t(0.4, 0.4);
	if (!startLvl(window))			
		return;
	pauseAndText(window, "УРА!!!", "Уровень 2 пройден!");
	update();// 3 lvl
	StartBombSpeed = Vector_t(0, 0.06);
	ScaleBomb = Vector_t(0.4, 0.4);
	if (!startLvl(window))			
		return;
	pauseAndText(window, "УРА!!!", "Уровень 3 пройден!");
	update();// 4 lvl
	StartBombSpeed = Vector_t(0, 0.06);
	ScaleBomb = Vector_t(0.3, 0.3);
	if (!startLvl(window))			
		return;
	pauseAndText(window, "УРА!!!", "Уровень 4 пройден!");
	update();// 5 lvl
	StartBombSpeed = Vector_t(0, 0.07);
	ScaleBomb = Vector_t(0.3, 0.3);
	if (!startLvl(window))			
		return;
	pauseAndText(window, "УРА!!!", "Уровень 5 пройден!");
	update();// 6 lvl
	StartBombSpeed = Vector_t(0, 0.09);
	ScaleBomb = Vector_t(0.3, 0.3);
	if (!startLvl(window))			
		return;
	pauseAndText(window, "УРА!!!", "Уровень 6 пройден!");
	update();// 7 lvl
	StartBombSpeed = Vector_t(0, 0.1);
	ScaleBomb = Vector_t(0.25, 0.25);
	if (!startLvl(window))			
		return;
	pauseAndText(window, "УРА!!!", "Игра пройдена!");
}

bool Game_t::startLvl(sf::RenderWindow &window)
{
	Gun_t gun(arrTexture[0]);
	sf::Clock clock;
	float time = 0, timer = 0;
	Key_t Keyboard;
	mainMusic.play();
	mainMusic.setLoop(true);
	while (window.isOpen())
	{
		Processe(window, Keyboard);
		if (Keyboard.escape)
		{
			mainMusic.stop();
			return false;
		}
		if (Keyboard.left)
			gun.move(LEFT, time, MinPositionX, MaxPositionX);
		else if (Keyboard.right)
			gun.move(RIGHT, time, MinPositionX, MaxPositionX);
		if (Keyboard.up)
		{
			arrBullet.push_back(gun.shot(arrTexture[0]));
			soundShot.setBuffer(*arrSoundBuff[0]);
			soundShot.play();
		}
		if (Keyboard.P)
		{
			pauseAndText(window, "Пауза");
			clock.restart();
		}
		for (auto it = arrBullet.begin(); it != arrBullet.end(); it++)
			(*it)->update(time);
		for (auto it = arrBomb.begin(); it != arrBomb.end(); it++)
			(*it)->update(time);
		if (timer > 2000)
		{
			Bomb_t bomb(Vector_t(rand() % (MaxPositionX - 20), MinPositionY - 10), arrTexture[1]);
			arrBomb.push_back(std::make_shared<Bomb_t>(bomb));
			timer = 0;
		}
		ExplosionCheck(time);
		BulletBorderCheck();
		BombBorderCheck();
		CollisionCheck();
		if (score >= 25)
		{
			mainMusic.stop();
			return true;
		}
		window.clear();
		time = (float)clock.getElapsedTime().asMilliseconds();
		timer += time;
		clock.restart();
		for (auto it = arrExplosion.begin(); it != arrExplosion.end(); it++)
			drawExplosion(window, arrTexture[2], (*it)->position);
		for (auto it = arrBullet.begin(); it != arrBullet.end(); it++)
			(*it)->draw(window, arrTexture[0]);
		for (auto it = arrBomb.begin(); it != arrBomb.end(); it++)
			(*it)->draw(window, arrTexture[1]);
		gun.draw(window, arrTexture[0]);
		drawScore(window);
		drawLvl(window);
		if (endGame)
		{
			mainMusic.stop();
			pauseAndText(window, "О нет...", "\tВы проиграли.", "Попробуйте еще раз!");
			return false;
		}
		window.display();
	}
	return false;
}

void Processe(sf::RenderWindow &window, Key_t &Keyboard)
{
	sf::Event event;
	Keyboard = { false, false, false, false, false, false, false, false, false };
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			Keyboard.escape = true;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			Keyboard.down = true;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			Keyboard.left = true;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			Keyboard.right = true;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			Keyboard.up = true;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			Keyboard.space = true;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			Keyboard.enter = true;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			Keyboard.lShift = true;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			Keyboard.P = true;
	}
}


void Game_t::ExplosionCheck(float time)
{
	for (auto it = arrExplosion.begin(); it != arrExplosion.end();)
	{
		it++;
		(*(it - 1))->time += time;
		if((*(it - 1))->time > 2500)
			it = arrExplosion.erase(it - 1);
	}
}

void Game_t::BulletBorderCheck()
{
	for (auto it = arrBullet.begin(); it != arrBullet.end(); )
	{
		Vector_t pos = (*it)->getPosition();
		it++;
		if (pos.getY() < MinPositionY - 40 || pos.getY() > MaxPositionY + 40)
			it = arrBullet.erase(it-1);
	}
}

void Game_t::BombBorderCheck()
{
	for (auto it = arrBomb.begin(); it != arrBomb.end(); it++)
	{
		Vector_t pos = (*it)->getPosition();
		if (pos.getY() < MinPositionY - 40 || pos.getY() > MaxPositionY - 20)
		{
			arrExplosion.push_back(std::make_shared<Explosion_t>(Explosion_t{ 0,
				(*it)->getPosition() - Vector_t(40, 40) }));
			endGame = true;
			break;
		}
	}
}

bool Game_t::CollisionObject(std::shared_ptr<Bullet_t> bullet, std::shared_ptr<Bomb_t> bomb)
{
	Vector_t posBomb = bomb->getPosition();
	Vector_t posBullet = bullet->getPosition();
	if (posBullet.getY() > posBomb.getY() + bomb->getSize().getY() ||
		posBullet.getY() + bullet->getSize().getY() < posBomb.getY())
		return false;
	if (posBullet.getX() + bullet->getSize().getX() < posBomb.getX() ||
		posBullet.getX() > posBomb.getX() + bomb->getSize().getX())
		return false;
	return true;
}

void Game_t::CollisionCheck()
{
	for (auto itBullet = arrBullet.begin(); itBullet != arrBullet.end();)
	{
		itBullet++;
		for (auto itBomb = arrBomb.begin(); itBomb != arrBomb.end();)
		{
			itBomb++;
			if (CollisionObject(*(itBullet - 1), *(itBomb - 1)))
			{
				arrExplosion.push_back(std::make_shared<Explosion_t>( Explosion_t{0, 
					(*(itBomb - 1))->getPosition() - Vector_t(35, 35) } ));
				itBomb = arrBomb.erase(itBomb - 1);
				itBullet = arrBullet.erase(itBullet - 1);
				soundExplosion.setBuffer(*arrSoundBuff[1]);
				soundExplosion.play();
				score++;
				break;
			}
		}
	}
}

void Game_t::drawExplosion(sf::RenderWindow &window, std::shared_ptr<sf::Texture> texture, Vector_t &position)
{
	sf::Sprite obj;
	obj.setTexture(*texture);
	obj.setScale((float)0.2, (float)0.2);
	obj.setPosition((float)position.getX(), (float)position.getY());
	window.draw(obj);
}

void Game_t::drawLvl(sf::RenderWindow &window)
{
	std::ostringstream playerScoreString;
	playerScoreString << lvl;
	sf::Text text("ВАШ УРОВЕНЬ = " + playerScoreString.str(), *arrFont[0], 15);
	text.setPosition(20, 10);
	window.draw(text);
}

void Game_t::drawScore(sf::RenderWindow &window)
{
	std::ostringstream playerScoreString;
	playerScoreString << score;
	sf::Text text("ВАШ СЧЁТ = " + playerScoreString.str(), *arrFont[0], 15);
	text.setPosition(260, 10);
	window.draw(text);
}

void Game_t::pauseAndText(sf::RenderWindow &window, const std::string &str1, const std::string &str2, const std::string &str3)
{
	Key_t Keyboard;
	sf::Text text;
	while (window.isOpen())
	{
		Processe(window, Keyboard);
		window.clear();
		text = sf::Text(str1, *arrFont[0], 35);
		text.setPosition((float)150, (float)200);
		window.draw(text);
		text = sf::Text(str2, *arrFont[0], 30);
		text.setPosition((float)80, (float)250);
		window.draw(text);
		text = sf::Text(str3, *arrFont[0], 25);
		text.setPosition((float)80, (float)300);
		window.draw(text);
		text = sf::Text("Для продолжения\n нажмите Enter", *arrFont[0], 25);
		text.setPosition((float)100, (float)400);
		window.draw(text);
		window.display();
		if (Keyboard.enter)
			return;
	}
}