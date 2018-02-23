#pragma once

#include "vector.h"
#include "object.h"
#include <memory>

static Vector_t StartBulletSpeed = Vector_t(0, 0.2);
static Vector_t ScaleBullet = Vector_t(0.1, 0.1);

class Bullet_t : public Object_t {
public:
	Bullet_t(Vector_t &_position, std::shared_ptr<sf::Texture> texture, Vector_t &_scale = ScaleBullet, Vector_t &_speed = StartBulletSpeed) :
		Object_t(texture, _position, _scale, _speed) {};
	void update(float time) { position -= speed * time; }
	void draw(sf::RenderWindow &window, std::shared_ptr<sf::Texture> texture)
	{
		sf::Sprite es;
		es.setTexture(*texture);
		es.setScale((float)scale.getX(), (float)scale.getY());
		es.setPosition((float)position.getX(), (float)position.getY());
		window.draw(es);
	}
};