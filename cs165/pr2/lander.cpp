/***********************************************************************
* Source File:
*    
* Author:
*    Keith Wheeler
* Summary:
*    
************************************************************************/


#include "lander.h"
#include "uiDraw.h"
#include <cassert>

/*Lander::Lander(float x, float y, float dx, float dy)
{
   destruction.setX(x);
   destruction.setY(y);
   destruction.setDx(dx);
   destruction.setDy(dy);
}
*/


void Lander :: draw(bool bDown, bool bLeft, bool bRight) const
{
   Point pos = destruction.getPoint();
   drawLander(pos);
   drawLanderFlames(pos, bDown, bLeft, bRight);
 
}

void Lander :: advance(bool bDown, bool bLeft, bool bRight)
{
   Velocity gr(0, 0, 0, -.15);
   destruction += gr;
   if (fuel)
   {
     float dx = 0;
     float dy = 0;
     
     if (bDown)
     { dy +=  .35; fuel--; }
     if (bLeft)
     { dx +=  .2; fuel--; }
     if (bRight)
     { dx += -.2; fuel--; }
     Velocity boost(0, 0, dx, dy);
     destruction += boost;
   }
   destruction++;
}
