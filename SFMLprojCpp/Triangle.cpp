#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::Triangle(Vector2f pos, float radius, Vector2f speed, float rotationSpeed)
	: GeometricalObject(pos, rotationSpeed, speed)
{
	shape = CircleShape(radius, 3);
	this->shape.setPosition(pos);
	this->shape.setOrigin(radius, radius);
	this->shape.setFillColor(Color(0, 0, 0, 0));
	this->shape.setOutlineThickness(10);
	this->shape.setOutlineColor(Color(0, 255, 0));
	this->setOrigin(shape.getOrigin());
}

Triangle::~Triangle()
{
}

void Triangle::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(shape);

	sf::CircleShape cshape(shape.getRadius());
	cshape.setPosition(shape.getPosition());
	cshape.setOrigin(shape.getOrigin());
	cshape.setFillColor(sf::Color(0, 0, 0, 0));
	cshape.setOutlineThickness(4);
	cshape.setOutlineColor(sf::Color(250, 150, 100));
	target.draw(cshape);
}

void Triangle::Update(Time dTime)
{
	shape.setPosition(Vector2f(shape.getPosition().x + getSpeed().x * (float)dTime.asMicroseconds() / 1000000,
							shape.getPosition().y + getSpeed().y * (float)dTime.asMicroseconds() / 1000000));
	shape.setRotation(shape.getRotation() + getRotationSpeed() * (float)dTime.asMicroseconds() / 1000000);

	this->setPos(shape.getPosition());
	this->setRotation(shape.getRotation());
}

FloatRect Triangle::getCollisionRect() const
{
	return shape.getGlobalBounds();
}

float Triangle::getRadius() const
{
	return shape.getRadius();
}

