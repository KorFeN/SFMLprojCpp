#include <SFML/Graphics.hpp>
#include "GameField.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::Default, settings);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	GameField gameField;
	gameField.addObject();
	gameField.addObject();
	gameField.addObject();
	gameField.addObject();

	sf::Clock dClock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		gameField.Update(dClock.getElapsedTime(), window);
		dClock.restart();

		window.clear();
		window.draw(gameField);

		window.display();

		
	}

	return 0;
}