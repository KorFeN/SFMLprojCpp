#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::Triangle(Vector2f pos, float radius, Vector2f speed, float rotationSpeed)
	: GeometricalObject(pos, rotationSpeed, speed)
{
	shape = CircleShape(radius, 3);
	this->shape.setFillColor(Color(0, 0, 0, 0));
	this->shape.setOutlineThickness(10);
	this->shape.setOutlineColor(Color(0, 255, 0));
}

Triangle::~Triangle()
{
}

void Triangle::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(shape);
}

void Triangle::Update(Time dTime)
{
	this->setPos(Vector2f(getPos().x + getSpeed().x * (float)dTime.asMicroseconds() / 1000000,
		getPos().y + getSpeed().y * (float)dTime.asMicroseconds() / 1000000));
	this->setRotation(getRotation() + getRotationSpeed() * (float)dTime.asMicroseconds() / 1000000);

	shape.setPosition(Vector2f(this->getPos().x, this->getPos().y));
	shape.setRotation(this->getRotation());
}

IntRect Triangle::getCollisionRect() const
{
	return IntRect(shape.getGlobalBounds());
}
