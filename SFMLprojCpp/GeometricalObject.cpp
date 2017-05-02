#include "GeometricalObject.h"

GeometricalObject::GeometricalObject()
{
	this->pos = Vector2f(100,100);
	this->rotationSpeed = 0;
	this->speed = Vector2f(0,0);
}

GeometricalObject::GeometricalObject(Vector2f pos, float rotationSpeed, Vector2f speed)
{
	this->pos = pos;
	this->rotationSpeed = rotationSpeed;
	this->speed = speed;
}

GeometricalObject::~GeometricalObject()
{
}

Vector2f GeometricalObject::getPos() const
{
	return this->pos;
}

Vector2f GeometricalObject::getSpeed() const
{
	return this->speed;
}

Vector2f GeometricalObject::getOrigin() const
{
	return this->origin;
}

float GeometricalObject::getRotationSpeed() const
{
	return this->rotationSpeed;
}

float GeometricalObject::getRotation() const
{
	return this->rotation;
}

void GeometricalObject::setPos(Vector2f pos)
{
	this->pos = pos;
}

void GeometricalObject::setRotation(float rotation)
{
	this->rotation = rotation;
}
