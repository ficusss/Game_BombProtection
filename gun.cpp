#include "gun.h"

void Gun_t::move(int signal, float time, int MinPositionX, int MaxPositionX)
{
	MaxPositionX -= (int)size.getX() - 5;
	if (signal == LEFT)
	{
		if (position.getX() - Shift.getX() * time + size.getX() / 2 >= MinPositionX)
			position -= Shift * time;
	}
	else
	{
		if (position.getX() + Shift.getX() * time - size.getX() / 2 <= MaxPositionX)
			position += Shift * time;
	}
}

void Gun_t::draw(sf::RenderWindow &window, std::shared_ptr<sf::Texture> texture)
{
	sf::Sprite es;
	es.setTexture(*texture);
	es.setScale((float)scale.getX(), (float)scale.getY());
	es.setPosition((float)position.getX(), (float)position.getY());
	window.draw(es);
}

std::shared_ptr<Bullet_t> Gun_t::shot(std::shared_ptr<sf::Texture> texture)
{
	Vector_t positionBullet(position.getX() + size.getX() / 2 - texture->getSize().x / 20, position.getY() - 10);
	return std::make_shared<Bullet_t>(positionBullet, texture);
}