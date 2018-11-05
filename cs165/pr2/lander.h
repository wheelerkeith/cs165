/***********************************************************************
* Header File:
*    
* Author:
*    Keith Wheeler
* Summary:
*    
************************************************************************/


#ifndef LANDER_H
#define LANDER_H

#include <iostream>
#include "velocity.h"
#include "uiDraw.h"
#include "uiInteract.h"
/*********************************************
* Lander
* The Lander.
*********************************************/
class Lander
{
public:
	// constructors
  Lander() : fuel(500), destruction(0, 0, -4, -4)   {}
	Lander(float x, float y, float dx, float dy);
	Lander(const Point & point) { *this = point; }

        Point getPoint()     const {return destruction.getPoint();}

	void draw(bool bUp, bool bLeft, bool bRight) const;
        void advance(bool bUp, bool bLeft, bool bRight);

private:
	int fuel;
	Velocity destruction;
};

#endif // LANDER_H
