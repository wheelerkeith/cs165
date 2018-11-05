#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class button
{
public:
	static sf::RenderWindow* pWndw;
	static int mseX;
	static int mseY;
	int posX;
	int posY;
	bool sel;
	bool mo;

	// functions
	virtual bool hit(void) = 0;
	virtual void draw(void) = 0;
	bool mseOver(void);

	// constructors
	button(void);
	button(int PosX, int PosY);

	// destructor
	virtual ~button(void);
};

#endif
