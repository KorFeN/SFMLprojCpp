#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "SFML\Graphics.hpp"
#include "GeometricalObject.h"

using namespace sf;

class Rectangle : public GeometricalObject
{
public:
	Rectangle();
	Rectangle(Vector2f pos, Vector2f size, Vector2f speed, float rotationSpeed);
	~Rectangle();

	virtual void draw(RenderTarget& target, RenderStates states) const;
	virtual void Update(Time dTime);
	virtual FloatRect getCollisionRect() const;

private:
	Vector2f size;
	RectangleShape shape;
};
#endif // !RECTANGLE_H
