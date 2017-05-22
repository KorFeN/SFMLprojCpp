#ifndef MENU_H
#define MENU_H

#include "SFML\Graphics.hpp"
#include "GameState.h"
#include <string>
#include <fstream>
#include "Highscore.h"

using namespace sf;

const std::string SCOREPATH = "highscores.txt";

class Menu : public Drawable
{
public:
	Menu();
	~Menu();

	virtual void draw(RenderTarget& target, RenderStates states) const;
	State Update(RenderWindow& window);

	void initScore(int highscore);
	void setMenu(State menuState);
	void sendKeyInput(Keyboard::Key key);

private:
	State menuState;
	int currentHighscore;
	Font font;
	Keyboard keyboard;
	Mouse mouse;
	std::string name;

	//MainMenu
	Text titleText;
	Text subText;
	Text start;
	Text quit;

	//ScoreBoard
	Text yourScore;
	Text enterName;
	Text nameText;
	Text topFive;
	Highscore* highscores;
	int scoresCount;
	bool acceptInput;
	

	void readFromFile(std::string path);
	void saveToFile(std::string path) const;
	std::string* stringSplit(std::string str) const;
	void sortHighscores();

	char keyToChar(Keyboard::Key key);

};
#endif // !MENU_H
