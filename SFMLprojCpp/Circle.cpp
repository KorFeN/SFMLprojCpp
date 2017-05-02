#include "Circle.h"
#include <iostream>

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
	this->setPos(Vector2f(getPos().x + getSpeed().x * (float)dTime.asMicroseconds() / 1000000,
						  getPos().y + getSpeed().y * (float)dTime.asMicroseconds() / 1000000));
	this->setRotation(getRotation() + getRotationSpeed() * (float)dTime.asMicroseconds() / 1000000);

	std::cout << (float)dTime.asMicroseconds() / 1000000 << std::endl;

	shape.setPosition(Vector2f(this->getPos().x, this->getPos().y));
	shape.setRotation(this->getRotation());
}

IntRect Circle::getCollisionRect() const
{
	return IntRect();
}
