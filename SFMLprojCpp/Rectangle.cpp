#include "Rectangle.h"

Rectangle::Rectangle() : GeometricalObject()
{
}

Rectangle::Rectangle(Vector2f pos, Vector2f size, Vector2f speed, float rotationSpeed)
	: GeometricalObject(pos, rotationSpeed, speed)
{
	this->size = size;
	this->shape.setOrigin(Vector2f(size.x / 2, size.y /2));
	this->shape.setFillColor(Color(0, 0, 0, 0));
	this->shape.setOutlineThickness(10);
	this->shape.setOutlineColor(Color(0, 255, 0));
	this->shape.setPosition(pos);
	this->shape.setRotation(this->getRotation());
	this->shape.setSize(size);
}

Rectangle::~Rectangle()
{
}

void Rectangle::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(shape);
}

void Rectangle::Update(Time dTime)
{
	this->setPos(Vector2f(getPos().x + getSpeed().x * (float)dTime.asMicroseconds() / 1000000,
		getPos().y + getSpeed().y * (float)dTime.asMicroseconds() / 1000000));
	this->setRotation(getRotation() + getRotationSpeed() * (float)dTime.asMicroseconds() / 1000000);

	shape.setPosition(Vector2f(this->getPos().x, this->getPos().y));
	shape.setRotation(this->getRotation());
}

IntRect Rectangle::getCollisionRect() const
{
	return IntRect(shape.getGlobalBounds());
}
