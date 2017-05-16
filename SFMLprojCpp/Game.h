#ifndef GAME_H
#define GAME_H
#include "SFML\Graphics.hpp"
#include "GameField.h"
#include "GeometricalObject.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Menu.h"
#include "GameState.h"

using namespace sf;

const int startSpawnRate = 3000000;
const int minSpawnRate = 300000;

class Game : public Drawable
{
public:
	Game();
	~Game();

	virtual void draw(RenderTarget& target, RenderStates states) const;
	virtual void Update(Time dTime, RenderWindow& window);
	bool getRunning() const;
	void sendKeyInput(Keyboard::Key key);

private:
	GameField gameField;
	State gameState;
	bool gameRunning;
	Menu menu;

	bool collision(Player player, GeometricalObject* object) const;

	//Spawn Logic variables
	long elapsedTime; //In Microseconds
	long spawnRate;
	long timeSinceLastSpawn;
};
#endif // !GAME_H