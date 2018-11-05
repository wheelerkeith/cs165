#ifndef BUTTONRECTDRAWN_H
#define BUTTONRECTDRAWN_H

#include "button.h"

class buttonRectDrawn :	public button
{
public:
	int szX;
	int szY;
	sf::String label;

	sf::Color selColor;
	sf::Color unSelColor;
	sf::Color moColor;
	sf::Color unMoColor;

	// functions
	virtual bool hit(void);
	virtual void draw(void);

	void INITlabel(const sf::Unicode::Text Label, int fontSize, sf::Color txtColor, char labelPos);

/*	void INITlabel(const sf::Unicode::Text Label, int relPosX, int relPosY, int fontSize, sf::Color txtColor)
	{
		label.SetText(Label);
		label.SetFont( sf::Font::GetDefaultFont() );
		label.SetColor(txtColor);
		label.SetPosition( static_cast<float>(posX+relPosX), static_cast<float>(posY+relPosY) );
		label.SetSize( static_cast<float>(fontSize) );
		return;
	}	*/

	// constructors
	buttonRectDrawn(void);
	buttonRectDrawn(int Posx, int PosY, int SzX, int SzY);

	// destructor
	~buttonRectDrawn(void);
};

#endif
