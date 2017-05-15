#ifndef PLAYER_H
#define PLAYER_H
#include "SFML\Graphics.hpp"
#include <iostream>

using namespace sf;

class Player : public Drawable
{
public:
	Player();
	~Player();

	virtual void draw(RenderTarget& target, RenderStates states) const;
	void update(Time dTime, RenderWindow& window);

	FloatRect getCollisionRect() const;
	Vector2f getPos() const;
	float getRadius() const;

private:
	Vector2f pos;
	Vector2f origin;

	Sprite sprite;
	Texture texture;
	
	Mouse mouse;
};


#endif // !PLAYER_H