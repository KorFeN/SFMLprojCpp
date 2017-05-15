#include "Player.h"

Player::Player()
{
	
	this->pos.x = 100;
	this->pos.y = 100;
	
	origin.x = 12.5f;
	origin.y = 12.5f;

	if (!texture.loadFromFile("Textures\\Cursor.png"))
		std::cout << "Could not load texture: Cursor.png" << std::endl;
	else
	{
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setColor(Color(255, 0, 100));
		sprite.setOrigin(origin);
	}
}

Player::~Player()
{
}

void Player::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(sprite, states);
}

void Player::update(Time dTime, RenderWindow& window)
{
	Vector2i mpos = mouse.getPosition(window);
	pos.x = (float)mpos.x;
	pos.y = (float)mpos.y;

	sprite.setPosition(pos);
}

FloatRect Player::getCollisionRect() const
{
	return sprite.getGlobalBounds();
}

Vector2f Player::getPos() const
{
	return pos;
}

float Player::getRadius() const
{
	return texture.getSize().x / 2;
}
