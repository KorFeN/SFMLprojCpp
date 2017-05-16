#include "Game.h"
#include <iostream>

Game::Game()
{
	this->gameState = _MAINMENU;
	this->gameRunning = true;
	this->spawnRate = startSpawnRate;
}

Game::~Game()
{
}

void Game::draw(RenderTarget & target, RenderStates states) const
{
	if(gameState == _INGAME)
		target.draw(gameField);
	if (gameState == _SCOREBOARD || gameState == _MAINMENU)
		target.draw(menu);
}

void Game::Update(Time dTime, RenderWindow & window)
{
	if (gameState == _INGAME)
	{
		// Object Spawn Logic
		elapsedTime += (long)dTime.asMicroseconds();
		timeSinceLastSpawn += (long)dTime.asMicroseconds();
		if (timeSinceLastSpawn > spawnRate)
		{
			gameField.addObject();
			timeSinceLastSpawn = timeSinceLastSpawn - spawnRate;
			spawnRate = startSpawnRate - (elapsedTime / 10);
			if (spawnRate < minSpawnRate)
				spawnRate = minSpawnRate;
		}

		gameField.Update(dTime, window);

		//Collision Logic
		GeometricalObject** objects = gameField.getObjectArray();
		int nrOfElements = gameField.getNrOfElements();
		Player player = gameField.getPlayer();
		for (int i = 0; i < nrOfElements; i++)
		{
			if (collision(player, objects[i]))
			{
				this->gameState = _SCOREBOARD;
				menu.initScore(elapsedTime / 1000000);
				menu.setMenu(_SCOREBOARD);
			}
		}
	}
	if (gameState == _SCOREBOARD || gameState == _MAINMENU)
	{
		gameState = menu.Update(window);
	}

	if (gameState == _QUIT)
	{
		gameRunning = false;
	}
}

bool Game::getRunning() const
{
	return this->gameRunning;
}

void Game::sendKeyInput(Keyboard::Key key)
{
	menu.sendKeyInput(key);
}

bool Game::collision(Player player, GeometricalObject* object) const
{
	bool collides = false;
	Circle* obj1 = dynamic_cast<Circle*>(object);
	Vector2f outLine(10, 10);
	Transform trans;

	if (obj1 != nullptr)
	{
		float xLen = player.getPos().x - obj1->getPos().x;
		float yLen = player.getPos().y - obj1->getPos().y;
		float distance = sqrt(pow(xLen, 2) + pow(yLen,2));
		if (distance < player.getRadius() + obj1->getRadius() + outLine.x)
			collides = true;
	}
	else
	{
		Rectangle* obj2 = dynamic_cast<Rectangle*>(object);
		if (obj2 != nullptr)
		{
			Vector2f pos(player.getPos().x, player.getPos().y);
			trans.rotate(360-(obj2->getRotation()), obj2->getPos());
			FloatRect playerRect(trans.transformPoint(pos) - Vector2f(12, 12), Vector2f(20, 20));
			FloatRect objRect(obj2->getPos() - obj2->getOrigin() - outLine, obj2->getOrigin() + obj2->getOrigin() + outLine + outLine);
			if (playerRect.intersects(objRect))
				collides = true;
		}
		else
		{
			Triangle* obj3 = dynamic_cast<Triangle*>(object);
			if (obj3 != nullptr)
			{
				/*Vector2f pos(player.getPos().x, player.getPos().y);
				trans.rotate(3 - (obj3->getRotation()), obj3->getPos());
				FloatRect playerRect(trans.transformPoint(pos) - Vector2f(12, 12), Vector2f(20, 20));
				Vector2f temp(obj3->getPos().x + obj3->getRadius(), obj3->getPos().y);
				trans.rotate(-30, obj3->getPos());
				Vector2f temp2 = temp;
				temp = trans.transformPoint(temp);
				if (playerRect.top - playerRect.height < temp.y)
				{
					if (FloatRect(temp2.x - (temp2.x - temp.x) * 2, temp.y, (temp2.x - temp.x) * 2, 40).intersects(playerRect))
						collides = true;
				}
				else
				{
					trans.rotate(180 - obj3->getRotation(), obj3->getPos());
					playerRect = FloatRect(trans.transformPoint(pos) - Vector2f(12, 12), Vector2f(20, 20));
					temp = Vector2f(obj3->getPos().x + obj3->getRadius(), obj3->getPos().y);
					trans.rotate(-30, obj3->getPos());
					temp2 = temp;
					temp = trans.transformPoint(temp);
					if (playerRect.top - playerRect.height < temp.y)
					{
						if (FloatRect(temp2.x - (temp2.x - temp.x) * 2, temp.y, (temp2.x - temp.x) * 2, 40).intersects(playerRect))
							collides = true;
					}
					else
					{
						trans.rotate(60 - obj3->getRotation(), obj3->getPos());
						playerRect = FloatRect(trans.transformPoint(pos) - Vector2f(12, 12), Vector2f(20, 20));
						temp = Vector2f(obj3->getPos().x + obj3->getRadius(), obj3->getPos().y);
						trans.rotate(-30, obj3->getPos());
						temp2 = temp;
						temp = trans.transformPoint(temp);
						if (playerRect.top - playerRect.height < temp.y)
						{
							if (FloatRect(temp2.x - (temp2.x - temp.x) * 2, temp.y, (temp2.x - temp.x) * 2, 10).intersects(playerRect))
								collides = true;
						}
					}
				}*/
			}
		}
	}

	return collides;
}