#pragma once
#include <vector>
#include <memory>
#include "bullet.h"
#include "bomb.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

static int STANDART_MinPositionX = 0;
static int STANDART_MinPositionY = 0;
static int STANDART_MaxPositionX = 400;
static int STANDART_MaxPositionY = 600;

typedef struct Key_tag {
	bool right;
	bool left;
	bool up;
	bool down;
	bool enter;
	bool space;
	bool escape;
	bool lShift;
	bool P;
}Key_t;

typedef struct Explosion_tag
{
	float time;
	Vector_t position;
} Explosion_t;

class Game_t {
	int MinPositionX;
	int MinPositionY;
	int MaxPositionX;
	int MaxPositionY;
	std::vector<std::shared_ptr<Bomb_t>> arrBomb;
	std::vector<std::shared_ptr<Bullet_t>> arrBullet;
	std::vector<std::shared_ptr<Explosion_t>> arrExplosion;
	std::vector<std::shared_ptr<sf::Texture>> arrTexture;
	std::vector<std::shared_ptr<sf::SoundBuffer>> arrSoundBuff;
	std::vector<std::shared_ptr<sf::Font>> arrFont;
	int score, lvl;
	sf::Sound soundShot, soundExplosion;
	sf::Music mainMusic;
	bool endGame;
public:
	Game_t();
	void startGame(sf::RenderWindow &window);
	bool startLvl(sf::RenderWindow &window);
private:
	void ExplosionCheck(float time);
	void BulletBorderCheck();
	void BombBorderCheck();
	void CollisionCheck();
	void drawExplosion(sf::RenderWindow &window, std::shared_ptr<sf::Texture> texture, Vector_t &position);
	bool CollisionObject(std::shared_ptr<Bullet_t> bullet, std::shared_ptr<Bomb_t> bomb);
	void drawScore(sf::RenderWindow &window);
	void Game_t::drawLvl(sf::RenderWindow &window);
	void update();
	void Game_t::pauseAndText(sf::RenderWindow &window, const std::string &str1 = "", const std::string &str2 = "", const std::string &str3 = "");
};

void Processe(sf::RenderWindow &window, Key_t &Keyboard);