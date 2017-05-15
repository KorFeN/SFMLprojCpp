#ifndef MENU_H
#define MENU_H

#include "SFML\Graphics.hpp"

using namespace sf;

class Menu : public Drawable
{
public:
	Menu();
	~Menu();

	virtual void draw(RenderTarget& target, RenderStates states) const;
	virtual void Update();

	void initScore(int highscore);
	void setMenu();

private:

};
#endif // !MENU_H
