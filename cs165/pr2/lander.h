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
//#include "uiInteract.h"
/*********************************************
* Lander
* The Lander.
*********************************************/
class Lander
{
public:
	// constructors
  Lander() : fuel(500)   {}
//	Lander(float x, float y, float dx, float dy);
//	Lander(const Point & point) { *this = point; }
  
  void draw(bool bDown, bool bLeft, bool bRight) const;
  void advance(bool bDown, bool bLeft, bool bRight);
        
  int getFuel()  { return fuel; }
  float getX()   { return destruction.getX(); }
  float getY()   { return destruction.getY(); }
  float getDx()  { return destruction.getDx(); }
  float getDy()  { return destruction.getDy(); }
  float getMag() { return destruction.getMag(); }
  Point getPoint()     const {return destruction.getPoint();}
  
  void setX(float x)   { destruction.setX(x); }
  void setY(float y)   { destruction.setY(y); }
  void setDx(float dx) { destruction.setDx(dx); }
  void setDy(float dy) { destruction.setDy(dy); }

private:
	int fuel;
	Velocity destruction;
};

#endif // LANDER_H
