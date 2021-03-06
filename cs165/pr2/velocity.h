/***********************************************************************
 * Header File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

#include <iostream>
#include "point.h"

/*********************************************
 *
 *********************************************/
class Velocity
{
public:
   // constructors
  Velocity()            : dx(0.0), dy(0.0) {dragon.setX(0.0); dragon.setY(0.0);}
   Velocity(float x, float y, float dx, float dy);

   // getters
   float getX()       const { return dragon.getX();              }
   float getY()       const { return dragon.getY();              }
   float getDx()      const { return dx;             }
   float getDy()      const { return dy;             }
   float getMag();
   Point getPoint() const
   {
      return dragon;
   }

   // setters
   void setX(float x);
   void setY(float y);
   void setDx(float dx);
   void setDy(float dy);
   void setPoint(const Point & pt)
   {
      dragon = pt;
   }

   friend bool operator >  (const Velocity & lhs, const float rhs);
   friend bool operator <  (const Velocity & lhs, const float rhs);
   friend bool operator >= (const Velocity & lhs, const float rhs);
   friend bool operator <= (const Velocity & lhs, const float rhs);
   friend double operator - (const Velocity & lhs, const Velocity & rhs);
   void operator = (const Velocity & rhs);
   void operator ++ (int postfix);
   void operator ++ ();
   Velocity operator + (const Velocity & v2);
   void operator += (Velocity & v2);




private:
   Point dragon;
   float dx;
   float dy;
   float mag;
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Velocity & pt);
bool operator == (const Velocity & lhs, const Velocity & rhs);
bool operator != (const Velocity & lhs, const Velocity & rhs);

#endif // POINT_H
