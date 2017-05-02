#include <SFML/Graphics.hpp>
#include "Player.h"
#include "GeometricalObject.h"
#include "Circle.h"
#include "Rectangle.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::Default, settings);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	Player player;
	Circle circle(Vector2f(100, 100), Vector2f(100, 100), 50);
	Rectangle rect1(Vector2f(700, 100), Vector2f(100, 40), Vector2f(-100, 100), 2000);

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
		circle.Update(dClock.getElapsedTime());
		rect1.Update(dClock.getElapsedTime());
		dClock.restart();

		window.clear();
		window.draw(player);
		window.draw(circle);
		window.draw(rect1);

		window.display();

		
	}

	return 0;
}