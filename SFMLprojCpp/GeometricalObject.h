#ifndef GEOMETRICALOBJECT_H
#define GEOMETRICALOBJECT_H
#include "SFML\Graphics.hpp"

using namespace sf;

class GeometricalObject : public Drawable
{
public:
	GeometricalObject();
	GeometricalObject(Vector2f pos, float rotationSpeed, Vector2f speed);
	~GeometricalObject();

	virtual void draw(RenderTarget& target, RenderStates states) const = 0;
	virtual void Update(Time dTime) = 0;
	virtual IntRect getCollisionRect() const = 0;
	Vector2f getPos() const;
	Vector2f getSpeed() const;
	Vector2f getOrigin() const;
	float getRotationSpeed() const;
	float getRotation() const;
	void setPos(Vector2f pos);
	void setRotation(float rotation);


private:
	Vector2f pos;
	Vector2f speed;
	float rotationSpeed;
	
	Vector2f origin;
	float rotation;
};


#endif // !GEOMETRICALOBJECT_H
