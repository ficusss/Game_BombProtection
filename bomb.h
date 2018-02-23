#pragma once

#include "object.h"
#include "vector.h"
#include <memory>
#include <SFML/Graphics.hpp>

static Vector_t StartBombSpeed = Vector_t(0, 0.05);
static Vector_t ScaleBomb = Vector_t(0.3, 0.3);

class Bomb_t : public Object_t {
public:
	Bomb_t(Vector_t &_position, std::shared_ptr<sf::Texture> texture, Vector_t &_scale = ScaleBomb, Vector_t& _speed = StartBombSpeed) :
		Object_t(texture, _position, _scale, _speed) {};
	void update(float time) { position += speed * time; }
	void draw(sf::RenderWindow &window, std::shared_ptr<sf::Texture> texture)
	{
		sf::Sprite es;
		es.setTexture(*texture);
		es.setScale((float)scale.getX(), (float)scale.getY());
		es.setPosition((float)position.getX(), (float)position.getY());
		window.draw(es);
	}
};