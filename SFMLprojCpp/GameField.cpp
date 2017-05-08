#include "GameField.h"

GameField::GameField()
{
	this->size = 3;
	this->nrOfElements = 0;
	
	objects = new GeometricalObject*[size];
	for (int i = 0; i < size; i++)
	{
		objects[i] = nullptr;
	}
}

GameField::~GameField()
{
	for (int i = 0; i < nrOfElements; i++)
	{
		delete objects[i];
		objects[i] = nullptr;
	}
	delete[] objects;
}

void GameField::draw(RenderTarget & target, RenderStates states) const
{
	for (int i = 0; i < nrOfElements; i++)
	{
		target.draw(*objects[i]);
	}
	target.draw(player);
}

void GameField::Update(Time dTime, RenderWindow& window)
{
	int indexOutsideBounds = -1;
	for (int i = 0; i < nrOfElements; i++)
	{
		objects[i]->Update(dTime);

		if (isObjectOutOfBounds(objects[i]))
			indexOutsideBounds = i;
	}

	if (indexOutsideBounds > -1)
		removeObject(indexOutsideBounds);

	player.update(dTime, window);
}

void GameField::addObject()
{
	if (nrOfElements == size)
	{
		expandArr(5);
	}
	Vector2f pos;
	Vector2f speed;
	getRandomSpeedPosition(&pos, &speed);
	int objType = rand() % 3;
	if (objType == 0)
	{
		int radius = rand() % 50 + 50;
		objects[nrOfElements] = new Circle(pos, speed, (float)radius);
	}
	else if (objType == 1)
	{
		Vector2f size((float)(rand() % 300 + 50), (float)(rand() % 300 + 50));
		float rotationSpeed = (float)(rand() % 100);
		objects[nrOfElements] = new Rectangle(pos, size, speed, rotationSpeed);
	}
	else if (objType == 2)
	{
		float radius = (float)(rand() % 50 + 50);
		float rotationSpeed = (float)(rand() % 100);
		objects[nrOfElements] = new Triangle(pos, radius, speed, rotationSpeed);
	}
	
	nrOfElements++;
}

void GameField::removeObject(int index)
{
	if (nrOfElements > 0 && index < nrOfElements)
	{
		if (index == nrOfElements - 1)
		{
			delete objects[index];
			objects[index] = nullptr;
		}
		else
		{
			delete objects[index];
			objects[index] = objects[nrOfElements-1];
			objects[nrOfElements - 1] = nullptr;
		}

		nrOfElements--;
	}
}

void GameField::expandArr(int expandAmount)
{
	GeometricalObject** temp = new GeometricalObject*[size + expandAmount];
	for (int i = 0; i < size; i++)
	{
		if(i < nrOfElements)
		{
			Circle* cast = dynamic_cast<Circle*>(objects[i]);
			if (cast != nullptr)
				temp[i] = new Circle(*cast);
			else
			{
				Rectangle* cast2 = dynamic_cast<Rectangle*>(objects[i]);
				if (cast != nullptr)
					temp[i] = new Rectangle(*cast2);
				else
				{
					Triangle* cast3 = dynamic_cast<Triangle*>(objects[i]);
					if (cast3 != nullptr)
						temp[i] = new Triangle(*cast3);
				}
			}
		}
		else
		{
			objects[i] = nullptr;
		}
	}
	for (int i = 0; i < nrOfElements; i++)
	{
		delete objects[i];
	}
	delete[] objects;
	
	objects = temp;
	size = size + expandAmount;
}

void GameField::getRandomSpeedPosition(Vector2f * pos, Vector2f * speed)
{
	int side = rand() % 4; //0 == up, 1==right, 2==down, 3== left

	if (side == 0) // UP
	{
		*pos = Vector2f((float)(rand() % 800), (float)(-80));
		*speed = Vector2f((float)(rand() % 100 - 50), (float)(rand() % 300 + 100));
	}
	else if (side == 1) // RIGHT
	{
		*pos = Vector2f((float)(880), (float)(rand() % 800));
		*speed = Vector2f((float)(-(rand() % 300 + 100)), (float)(rand() % 100 - 50));
	}
	else if(side == 2) // DOWN
	{ 
		*pos = Vector2f((float)(rand() % 800), (float)(880));
		*speed = Vector2f((float)(rand() % 100 - 50), (float)(-(rand() % 300 + 100)));
	}
	else if (side == 3) // LEFT
	{
		*pos = Vector2f((float)(-80), (float)(rand() % 800));
		*speed = Vector2f((float)(rand() % 300 + 100), (float)(rand() % 100 - 50));
	}
}

bool GameField::isObjectOutOfBounds(GeometricalObject* obj) const
{
	bool isOut = false;
	Vector2f pos = obj->getPos();

	if (pos.x < -100 || pos.x > 900 || pos.y < -100 || pos.y > 900)
		isOut = true;

	return isOut;
}

