/***********************************************************************
 * Header File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/


#ifndef SHIP_H
#define SHIP_H

#include <cmath>
#include <iostream>
#include "uiDraw.h"
#include "point.h"
#include "velocity.h"


class Ship
{
public:
   // constructors
   inline void draw(int rotate)
   {
      Point pos = destruction.getPoint();
      drawShip(pos, rotate);
   }

   void move(int up, int down, int left, int right, int rotate)
   {
      const float PI = 3.14159f;
      if (left)
      {
         pos
         rotate += (left + 9) / 5;
      }
      if (right)
      {
         rotate += (right + 9) / 5;
      }
   }
   
   void rotate()
   {
      
   }

   // getters


   // setters


private:
   Velocity destruction;
   Point pos;

};
#endif // SHIP_H