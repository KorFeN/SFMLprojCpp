#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 800), "Stay Alive", sf::Style::Default, settings);
	window.setMouseCursorVisible(true);

	Game game;
	

	sf::Clock dClock;

	Keyboard::Key prevKey = Keyboard::LControl;

	while (window.isOpen() && game.getRunning() == true)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code != prevKey)
					game.sendKeyInput(event.key.code);
				prevKey = event.key.code;
			}
			if (event.type == sf::Event::KeyReleased)
			{
				prevKey = Keyboard::LControl;
			}
		}

		game.Update(dClock.getElapsedTime(), window);
		dClock.restart();

		window.clear();
		window.draw(game);

		window.display();
	}
	return 0;
}