#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "SFML\Graphics.hpp"
#include "Player.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"

using namespace sf;

class GameField : public Drawable
{
public:
	GameField();
	~GameField();

	virtual void draw(RenderTarget& target, RenderStates states) const;
	virtual void Update(Time dTime, RenderWindow& window);
	void addObject();


private:
	Player player;
	GeometricalObject** objects;
	int size;
	int nrOfElements;

	void removeObject(int index);
	void expandArr(int expandAmount);
	void getRandomSpeedPosition(Vector2f * pos, Vector2f * speed);
	bool isObjectOutOfBounds(GeometricalObject* obj) const;
};

#endif // !GAMEFIELD_H
