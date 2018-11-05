#include "button.h"

int button::mseX = 0;
int button::mseY = 0;
sf::RenderWindow* button::pWndw = NULL;

button::button(void)
{
	posX = 0;
	posY = 0;
	sel = false;
	mo = false;
}

button::button(int PosX, int PosY)
{
	posX = PosX;
	posY = PosY;
	sel = false;
	mo = false;
}

button::~button(void)
{
}

bool button::mseOver(void)
{
	if( hit() )
		mo = true;
	else
		mo = false;
	return mo;
}
