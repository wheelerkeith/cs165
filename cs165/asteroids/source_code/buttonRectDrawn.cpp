#include "buttonRectDrawn.h"

buttonRectDrawn::buttonRectDrawn(void)
{
	szX = 10;
	szY = 10;
//	label = "";
	selColor = sf::Color(255,0,0);
	unSelColor = sf::Color(0,255,0);
	moColor = sf::Color(255,255,102);// yellow
	unMoColor = sf::Color(153,153,153);// grey
}

buttonRectDrawn::buttonRectDrawn(int PosX, int PosY, int SzX, int SzY):button(PosX, PosY)
{
	szX = SzX;
	szY = SzY;

	selColor = sf::Color(0,255,0);// green
	unSelColor = sf::Color(255,0,0);// red
	moColor = sf::Color(255,255,102);// yellow
	unMoColor = sf::Color(153,153,153);// grey
}

buttonRectDrawn::~buttonRectDrawn(void)
{
}

bool buttonRectDrawn::hit(void)
{
	if( (mseX > posX) && (mseX < posX+szX) && (mseY > posY) && (mseY < posY+szY) )
		return true;
	return false;
}

void buttonRectDrawn::draw(void)
{
	sf::Color sColor = sel ? selColor : unSelColor;
	sf::Color mColor = mo ? moColor : unMoColor;

	sf::Shape Rect = sf::Shape::Rectangle(static_cast<float>(posX), static_cast<float>(posY),
		static_cast<float>(posX+szX), static_cast<float>(posY+szY), sColor, 1.0f, mColor);

	if( pWndw )
	{
		pWndw->Draw(Rect);
		pWndw->Draw(label);
	}

	return;
}

void buttonRectDrawn::INITlabel(const sf::Unicode::Text Label, int fontSize, sf::Color txtColor, char labelPos)
{
	float fposX = static_cast<float>(posX);// fix this!
	float fposY = static_cast<float>(posY);
	float fszX = static_cast<float>(szX);
	float fszY = static_cast<float>(szY);

	label.SetText(Label);
	label.SetFont( sf::Font::GetDefaultFont() );
	label.SetColor(txtColor);
	label.SetPosition( fposX, fposY );
	label.SetSize( static_cast<float>(fontSize) );

	sf::FloatRect sR = label.GetRect();
	float len = sR.GetWidth();
	float hgt = sR.GetHeight();

	switch(labelPos)
	{
	case 'c':// centered
		label.SetX( (2.0f*fposX + fszX - len)/2.0f );
		label.SetY( (2.0f*fposY + fszY - hgt)/2.0f - 1.5f );
		break;
	case 'l':// left side
		label.SetX( fposX - len - 3.0f );
		label.SetY( (2.0f*fposY + fszY - hgt)/2.0f - 1.5f );
		break;
	case 'r':// right side
		label.SetX( fposX +fszX + 3.0f );
		label.SetY( (2.0f*fposY + fszY - hgt)/2.0f - 1.5f );
		break;
	case 't':// on top
		label.SetX( (2.0f*fposX + fszX - len)/2.0f );
		label.SetY( fposY - hgt - 3.0f );
		break;
	case 'b':// below
		label.SetX( (2.0f*fposX + fszX - len)/2.0f );
		label.SetY( fposY +fszY - 1.0f );
		break;
	default:
		break;
	}

	return;
}
