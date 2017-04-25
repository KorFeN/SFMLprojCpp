#ifndef GEOMETRICALOBJECT_H
#define GEOMETRICALOBJECT_H
#include "SFML\Graphics.hpp"

using namespace sf;

class GeometricalObject : public Drawable
{
public:
	GeometricalObject();
	virtual ~GeometricalObject() = 0;
	virtual void draw(RenderTarget& target, RenderStates states) const = 0;
	virtual void Update(Time dTime) = 0;
	virtual IntRect getCollisionRect() const = 0;

private:
	Vector2f pos;
	Vector2f origin;
	float rotation;

	float rotaionSpeed;
	Vector2f speed;
};


#endif // !GEOMETRICALOBJECT_H
