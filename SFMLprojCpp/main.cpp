#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::Default, settings);
	window.setMouseCursorVisible(false);

	Game game;

	sf::Clock dClock;

	while (window.isOpen() && game.getRunning() == true)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		game.Update(dClock.getElapsedTime(), window);
		dClock.restart();

		window.clear();
		window.draw(game);

		window.display();
	}
	return 0;
}