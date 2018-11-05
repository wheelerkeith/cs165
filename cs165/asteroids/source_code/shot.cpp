#include "shot.h"

shot::shot(void)
{
	setNum = cellNum = 0;
	posx = posy = 0.0f;
	velx = vely = 0.0f;
	inAir = false;
}

shot::~shot(void)
{
}

void shot::move(void)
{
	posx += velx;
	posy += vely;
	if(posx > static_cast<float>(pGR->right) )
	{
		inAir = false;
		return;
	}
	if(posx < static_cast<float>(pGR->left) )
	{
		inAir = false;
		return;
	}
	if(posy > static_cast<float>(pGR->bottom) )
	{
		inAir = false;
		return;
	}
	if(posy < static_cast<float>(pGR->top) )
	{
		inAir = false;
		return;
	}
}// end of move()

void shot::draw(void)
{
	pImgSet->drawCell( setNum, cellNum, posx, posy );
	return;
}

void shot::INIT(const float& posX, const float& posY, const float& velX, const float& velY )
{
	posx = posX;
	posy = posY;
	velx = velX;
	vely = velY;
	inAir = true;
	return;
}
