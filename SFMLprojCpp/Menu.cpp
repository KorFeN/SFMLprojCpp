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

		topFive.setFont(font);
		topFive.setString("");
		topFive.setCharacterSize(40);
		topFive.setFillColor(Color(255, 255, 255));
		topFive.setPosition(Vector2f(260, 200));

	}
	acceptInput = true;
	scoresCount = 0;
}

Menu::~Menu()
{
	delete[] highscores;
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
		target.draw(topFive);
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
				window.setMouseCursorVisible(false);
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

		if (scoresCount > 0)
		{
			topFive.setString("");
			for (int i = 0; i < 5; i++)
			{
				if (scoresCount > i)
				{
					topFive.setString(topFive.getString() + "\n" + std::to_string(highscores[i].getScore()) + " " + highscores[i].getName());
				}
			}
		}

		return _SCOREBOARD;
	}
}

void Menu::initScore(int highscore)
{
	this->currentHighscore = highscore;
	this->yourScore.setString("Your score: " + std::to_string(highscore));
	readFromFile(SCOREPATH);
}

void Menu::setMenu(State menuState)
{
	this->menuState = menuState;
}

void Menu::sendKeyInput(Keyboard::Key key)
{
	if (menuState == _SCOREBOARD)
	{
		if (key == Keyboard::Return && acceptInput == true)
		{
			acceptInput = false;
			highscores[scoresCount] = Highscore(currentHighscore, name);
			scoresCount++;
			sortHighscores();
			name = "";
			saveToFile(SCOREPATH);
		}
		else
		{
			char keyChar = keyToChar(key);
			if (keyChar != '\0' && acceptInput == true)
				name += keyChar;
		}
	}	
}

void Menu::readFromFile(std::string path)
{
	ifstream stream;
	stream.open(path);

	int currentHSIndx = 0;
	int score = 0;
	string name = "";


	while (!stream.eof())
	{
		string input;
		getline(stream, input);

		string* splInput = stringSplit(input);

		if (splInput[0] == "<count>")
		{
			this->scoresCount = stoi(splInput[1]);
			highscores = new Highscore[scoresCount + 1];
		}
		else if (splInput[0] == "<score>")
		{
			score = stoi(splInput[1]);
		}
		else if (splInput[0] == "<name>")
		{
			name = splInput[1];
		}
		else if (splInput[0] == "<endHighscore>")
		{
			highscores[currentHSIndx] = Highscore(score,name);
			currentHSIndx++;
			score = 0;
			name = "";
		}

		delete[](splInput);
	}

	stream.close();
}

void Menu::saveToFile(std::string path) const
{
	std::ofstream stream;
	stream.open(path);
	stream << "<count> " + std::to_string(scoresCount);
	for (int i = 0; i < scoresCount; i++)
	{
		stream << std::endl << std::endl << "<score> " + std::to_string(highscores[i].getScore()) << std::endl;
		stream << "<name> " + highscores[i].getName() << std::endl;
		stream << "<endHighscore>";
	}
	stream.close();
}

std::string * Menu::stringSplit(std::string str) const
{
	std::string str1 = "";
	std::string str2 = "";
	bool firstWord = true;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ' && firstWord == true)
		{
			firstWord = false;
		}
		else
		{
			if (firstWord)
			{
				str1.append(1, str[i]);
			}
			else
			{
				str2.append(1, str[i]);
			}
		}
	}

	return new std::string[2]{ str1, str2 };
}

void Menu::sortHighscores()
{
	
	for (int i = (scoresCount - 1); i >= 0; i--)
	{
		for (int k = (scoresCount - i - 1); k >= 0 ; k--)
		{
			if (highscores[k].getScore() > highscores[k - 1].getScore())
			{
				Highscore temp = highscores[k];
				highscores[k] = highscores[k - 1];
				highscores[k - 1] = temp;
			}
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

