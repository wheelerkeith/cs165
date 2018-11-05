/***********************************************************************
 * Source File:
 *    Rifle : A gun
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The implementation file for the Rifle class, one component
 *    of the Skeet game
 ************************************************************************/

#include <cassert>

#include "point.h"
#include "uiDraw.h"
#include "rifle.h"

/*****************************************
 * RIFLE : DRAW
 * Draw the rifle in the bottom right corner
 *****************************************/
void Rifle::draw() const
{
   // make the point static so we don't have to chagne it.
   static const Point point;
   Point corner(point.getXMax(), point.getYMin());
   
   drawRect(corner /* position */, 
            5 /* width */, 
            40 /* height */, 
            90 - angle);
   
   assert(angle >= 0 && angle <= 90);
}

/*******************************************
 * RIFLE : MOVE
 * Move the rifle up or down
 *****************************************/
void Rifle::move(int up, int down)
{
   // make sure we get rational data from the caller
   assert(up >= 0 && down >= 0);
   
   // adjust the angle, taking key acceleration into account
   if (up)
      angle += (up   + 9) / 5;
   if (down)
      angle -= (down + 5) / 5;
   
   // make sure the rifle does not point some crazy way
   if (angle > 90)
      angle = 90;
   if (angle < 0)
      angle = 0;
   
   // make sure it is rational
   assert(angle >= 0 && angle <= 90);
}
