#pragma once

#include "vector.h"
#include "bullet.h"
#include "object.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

static Vector_t ZeroSpeed = Vector_t(0, 0);
static Vector_t StartGunPosition = Vector_t(170, 550);
static Vector_t ScaleGun = Vector_t(0.3, 0.3);
static Vector_t Shift = Vector_t(0.5, 0);
enum Shift {RIGHT, LEFT};

class Gun_t : private Object_t {
	int countBullet;
public:
	Gun_t(std::shared_ptr<sf::Texture> texture, Vector_t &_position = StartGunPosition, Vector_t &_scale = ScaleGun, Vector_t &_speed = ZeroSpeed) :
		Object_t(texture, _position, _scale, _speed)
	{
		countBullet = 0; 
	};
	void move(int signal, float time, int MinPositionX, int MaxPositionX);
	void draw(sf::RenderWindow &window, std::shared_ptr<sf::Texture> texture);
	std::shared_ptr<Bullet_t> shot(std::shared_ptr<sf::Texture> texture);
};
	