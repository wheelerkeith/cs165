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

   void move(int up, int down, int left, int right, int &rotate)
   {
      float dx = 0;
      float dy = 0;
      if (left)
         rotate += (left + 9) / 5;
      if (right)
         rotate -= (right + 9) / 5;
      if (up)
      {
         dx += up*sin(M_PI*rotate/180.0);
         dy += up*cos(M_PI*rotate/180.0);
      }
      if (down)
      {
      }
      destruction.addX(dx);
      destruction.addY(dy);
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