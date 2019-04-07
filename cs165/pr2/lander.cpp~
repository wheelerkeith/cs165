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

Lander::Lander(float x, float y, float dx, float dy)
{
   destruction.setX(x);
   destruction.setY(y);
   destruction.setDx(dx);
   destruction.setDy(dy);
}


void Lander :: draw(bool bUp, bool bLeft, bool bRight) const
{
   Point pos = destruction.getPoint();
   Point ptF;
   ptF.setX(-175);
   ptF.setY(175);
   drawLander(pos);
   drawLanderFlames(pos, bUp, bLeft, bRight);
   drawNumber(ptF, fuel);
   
}

void Lander :: advance(bool bUp, bool bLeft, bool bRight)
{
   destruction.setX(157);
   destruction.setY(175);
   Velocity gr(0, 0, 0, -4);
   Velocity left(0, 0, 0, 0);

   if (fuel)
   {
      if (bRight)
      {
         Velocity left(0, 0, -4, 0);
         destruction += left;
         fuel--;
      }
      if (bLeft)
      {
         Velocity left(0, 0, 4, 0);
         destruction += left;
         fuel--;
      }
      if (bUp)
      {
         Velocity left(0, 0, 0, 8);
         destruction += left;
         fuel--;
      }
   }
   destruction += gr;
   destruction++;
   draw(bUp, bLeft, bRight);
}
