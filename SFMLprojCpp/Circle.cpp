#include "Circle.h"

Circle::Circle() : GeometricalObject()
{
	this->radius = 0;
}

Circle::Circle(Vector2f pos, Vector2f speed, float radius)
	: GeometricalObject(pos, 0, speed)
{
	this->radius = radius;
	this->shape.setRadius(radius);
	this->shape.setFillColor(Color(0, 0, 0, 0));
	this->shape.setOutlineThickness(10);
	this->shape.setOutlineColor(Color(0, 255, 0));
	this->shape.setPosition(pos);
	this->shape.setOrigin(radius, radius);
	this->setOrigin(Vector2f(radius, radius));
}

Circle::~Circle()
{
}

void Circle::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(shape);
}

void Circle::Update(Time dTime)
{
	shape.setPosition(Vector2f(shape.getPosition().x + getSpeed().x * (float)dTime.asMicroseconds() / 1000000,
							shape.getPosition().y + getSpeed().y * (float)dTime.asMicroseconds() / 1000000));
	shape.setRotation(shape.getRotation() + getRotationSpeed() * (float)dTime.asMicroseconds() / 1000000);

	this->setPos(shape.getPosition());
	this->setRotation(shape.getRotation());
}

FloatRect Circle::getCollisionRect() const
{
	return shape.getGlobalBounds();
}

int Circle::getRadius() const
{
	return this->radius;
}
