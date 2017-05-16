#ifndef MENU_H
#define MENU_H

#include "SFML\Graphics.hpp"
#include "GameState.h"
#include <string>

using namespace sf;

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

	char keyToChar(Keyboard::Key key);

};
#endif // !MENU_H
