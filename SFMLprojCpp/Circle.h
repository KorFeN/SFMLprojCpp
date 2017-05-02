#ifndef CIRCLE_H
#define CIRCLE_H
#include "SFML\Graphics.hpp"
#include "GeometricalObject.h"

using namespace sf;

class Circle : public GeometricalObject
{
public:
	Circle();
	Circle(Vector2f pos, Vector2f speed, float radius);
	~Circle();

	virtual void draw(RenderTarget& target, RenderStates states) const;
	virtual void Update(Time dTime);
	virtual IntRect getCollisionRect() const;

private:
	float radius;
	CircleShape shape;
};


#endif // !CIRCLE_H
