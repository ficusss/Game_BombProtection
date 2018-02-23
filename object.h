#pragma once

#include "vector.h"
#include <SFML/Graphics.hpp>
#include <memory>


class Object_t {
protected:
	Vector_t position;
	Vector_t scale;
	Vector_t speed;
	Vector_t size;
public:
	Object_t(std::shared_ptr<sf::Texture> texture, Vector_t &_position, Vector_t &_scale, Vector_t &_speed) :
		position(_position), scale(_scale), speed(_speed) 
	{
		size = Vector_t(texture->getSize().x * scale.getX(), texture->getSize().y * scale.getY());
	};
	virtual ~Object_t() {};
	Vector_t getPosition() { return position; }
	Vector_t getScale() { return scale; }
	Vector_t getSize() { return size; }
	Vector_t getSpeed() { return speed; }
	virtual void draw(sf::RenderWindow &window, std::shared_ptr<sf::Texture> texture)
	{
		sf::Sprite es;
		es.setTexture(*texture);
		es.setScale((float)scale.getX(), (float)scale.getY());
		es.setPosition((float)position.getX(), (float)position.getY());
		window.draw(es);
	}
};