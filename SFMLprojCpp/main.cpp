#include <SFML/Graphics.hpp>
#include "Player.h"
#include "GeometricalObject.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::Default, settings);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	Player player;

	sf::Clock dClock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		player.update(dClock.getElapsedTime(), window);

		window.clear();
		window.draw(player);

		window.display();

		dClock.restart();
	}

	return 0;
}