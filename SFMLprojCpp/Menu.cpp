#include "Menu.h"
#include <iostream>

Menu::Menu()
{
	this->menuState = _MAINMENU;
	name = "";

	if (!font.loadFromFile("Fonts\\IMFeENit29P.ttf"))
	{
		std::cout << "ERROR: Could not load font IMFELLENGLISH" << std::endl;
	}
	else
	{
		//TITLE SCREEN
		titleText.setFont(font);
		titleText.setString("Stay Alive");
		titleText.setCharacterSize(60);
		titleText.setFillColor(Color(255, 255, 255));
		titleText.setPosition(Vector2f(300, 120));

		subText.setFont(font);
		subText.setString("Game project by Jesper Samuelsson");
		subText.setCharacterSize(24);
		subText.setFillColor(Color(255, 255, 255));
		subText.setPosition(Vector2f(250, 200));

		start.setFont(font);
		start.setString("Play");
		start.setCharacterSize(50);
		start.setFillColor(Color(255, 255, 255));
		start.setPosition(Vector2f(360, 360));

		quit.setFont(font);
		quit.setString("Quit");
		quit.setCharacterSize(50);
		quit.setFillColor(Color(255, 255, 255));
		quit.setPosition(Vector2f(360, 500));


		//SCOREMENU
		yourScore.setFont(font);
		yourScore.setCharacterSize(60);
		yourScore.setFillColor(Color(255, 255, 255));
		yourScore.setPosition(Vector2f(300, 100));

		enterName.setFont(font);
		enterName.setString("Enter your name:");
		enterName.setCharacterSize(40);
		enterName.setFillColor(Color(255, 255, 255));
		enterName.setPosition(Vector2f(260, 160));

		nameText.setFont(font);
		nameText.setString("");
		nameText.setCharacterSize(40);
		nameText.setFillColor(Color(255, 255, 255));
		nameText.setPosition(Vector2f(260, 200));

	}
}

Menu::~Menu()
{
}

void Menu::draw(RenderTarget & target, RenderStates states) const
{
	if (menuState == _MAINMENU)
	{
		target.draw(titleText);
		target.draw(subText);
		target.draw(start);
		target.draw(quit);
	}
	if (menuState == _SCOREBOARD)
	{
		target.draw(yourScore);
		target.draw(enterName);
		target.draw(nameText);
		target.draw(quit);
	}
}

State Menu::Update(RenderWindow& window)
{
	if (menuState == _MAINMENU)
	{
		if(IntRect(360,360,81,50).contains(mouse.getPosition(window)))
		{
			//You are hovering over Play Button
			start.setFillColor(Color(255, 100, 100));
			if (mouse.isButtonPressed(mouse.Left))
			{
				return _INGAME;
			}
		}
		else
		{
			start.setFillColor(Color(255, 255, 255));
		}

		if (IntRect(360, 500, 90, 65).contains(mouse.getPosition(window)))
		{
			//You are hovering over Play Button
			quit.setFillColor(Color(255, 100, 100));
			if (mouse.isButtonPressed(mouse.Left))
			{
				return _QUIT;
			}
		}
		else
		{
			quit.setFillColor(Color(255, 255, 255));
		}
		return _MAINMENU;
	}
	if (menuState == _SCOREBOARD)
	{
		nameText.setString(name);

		if (IntRect(360, 500, 90, 65).contains(mouse.getPosition(window)))
		{
			//You are hovering over Play Button
			quit.setFillColor(Color(255, 100, 100));
			if (mouse.isButtonPressed(mouse.Left))
			{
				return _QUIT;
			}
		}
		else
		{
			quit.setFillColor(Color(255, 255, 255));
		}

		return _SCOREBOARD;
	}
}

void Menu::initScore(int highscore)
{
	this->currentHighscore = highscore;
	this->yourScore.setString("Your score: " + std::to_string(highscore));
}

void Menu::setMenu(State menuState)
{
	this->menuState = menuState;
}

void Menu::sendKeyInput(Keyboard::Key key)
{
	if (menuState == _SCOREBOARD)
	{
		if (key == Keyboard::Return)
		{

		}
		else
		{
			char keyChar = keyToChar(key);
			if (keyChar != '\0')
				name += keyChar;
		}
	}	
}

char Menu::keyToChar(Keyboard::Key key)
{
	char keyChar = '\0';
	switch (key)
	{
	case sf::Keyboard::A:
		keyChar = 'a';
		break;
	case sf::Keyboard::B:
		keyChar = 'b';
		break;
	case sf::Keyboard::C:
		keyChar = 'c';
		break;
	case sf::Keyboard::D:
		keyChar = 'd';
		break;
	case sf::Keyboard::E:
		keyChar = 'e';
		break;
	case sf::Keyboard::F:
		keyChar = 'f';
		break;
	case sf::Keyboard::G:
		keyChar = 'g';
		break;
	case sf::Keyboard::H:
		keyChar = 'h';
		break;
	case sf::Keyboard::I:
		keyChar = 'i';
		break;
	case sf::Keyboard::J:
		keyChar = 'j';
		break;
	case sf::Keyboard::K:
		keyChar = 'k';
		break;
	case sf::Keyboard::L:
		keyChar = 'l';
		break;
	case sf::Keyboard::M:
		keyChar = 'm';
		break;
	case sf::Keyboard::N:
		keyChar = 'n';
		break;
	case sf::Keyboard::O:
		keyChar = 'o';
		break;
	case sf::Keyboard::P:
		keyChar = 'p';
		break;
	case sf::Keyboard::Q:
		keyChar = 'q';
		break;
	case sf::Keyboard::R:
		keyChar = 'r';
		break;
	case sf::Keyboard::S:
		keyChar = 's';
		break;
	case sf::Keyboard::T:
		keyChar = 't';
		break;
	case sf::Keyboard::U:
		keyChar = 'u';
		break;
	case sf::Keyboard::V:
		keyChar = 'v';
		break;
	case sf::Keyboard::W:
		keyChar = 'w';
		break;
	case sf::Keyboard::X:
		keyChar = 'x';
		break;
	case sf::Keyboard::Y:
		keyChar = 'y';
		break;
	case sf::Keyboard::Z:
		keyChar = 'z';
		break;
	default:
		break;
	}
	return keyChar;
}

