#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "SFML\Graphics.hpp"
#include "GeometricalObject.h"

using namespace sf;

class Triangle : public GeometricalObject
{
public:
	Triangle();
	Triangle(Vector2f pos, float radius, Vector2f speed, float rotationSpeed);
	~Triangle();

	virtual void draw(RenderTarget& target, RenderStates states) const;
	virtual void Update(Time dTime);
	virtual IntRect getCollisionRect() const;

private:
	float radius;
	CircleShape shape;
};

#endif // !TRIANGLE_H
