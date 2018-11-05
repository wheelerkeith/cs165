/***********************************************************************
 * Source File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/



#include "velocity.h"
#include <cassert>
#include <cmath>

/******************************************
 * POINT : CONSTRUCTOR WITH X,Y
 * Initialize the point to the passed position
 *****************************************/
Velocity::Velocity(float x, float y, float dx, float dy) : dx(dx), dy(dy)
{
   dragon.setX(x);
   dragon.setY(y);
}

/*******************************************
 * POINT : SET X
 * Set the x position if the value is within range
 *******************************************/
void Velocity::setX(float x)
{
   dragon.setX(x);
}

/********************************************
 * POINT : Assignmenet
 *******************************************/
bool operator == (const Velocity & lhs, const Velocity & rhs)
{
   if (int (lhs.getX()  * 1000)       == int (rhs.getX()  * 1000)&&
       int (lhs.getY()  * 1000)       == int (rhs.getY()  * 1000)&&
       int (lhs.getDx() * 1000)       == int (rhs.getDx() * 1000)&&
       int (lhs.getDy() * 1000)       == int (rhs.getDy() * 1000))
      return true;
   else
      return false;
}

bool operator != (const Velocity & lhs, const Velocity & rhs)
{
   return !(lhs == rhs);
}

bool operator > (const Velocity &lhs, const float rhs)
{
   return (sqrt(pow(lhs.getDx(), 2) + pow(lhs.getDy(), 2)) > rhs);
}

bool operator < (const Velocity &lhs, const float rhs)
{
   return (sqrt(pow(lhs.getDx(), 2) + pow(lhs.getDy(), 2)) < rhs);
}
bool operator >= (const Velocity &lhs, const float rhs)
{
   return (sqrt(pow(lhs.dx, 2) + pow(lhs.dy, 2)) >= rhs);
}

bool operator <= (const Velocity &lhs, const float rhs)
{
   return (sqrt(pow(lhs.dx, 2) + pow(lhs.dy, 2)) <= rhs);
}

float operator - (const Velocity &lhs, const Velocity &rhs)
{
   float slicePercent = 1 / fmaxf((std::abs (lhs.dx) + std::abs (lhs.dy))
                                  , (std::abs (rhs.dx) + std::abs (rhs.dy)));
   float vel;
   float minDistance;
   float distanceSquared;

   for (float percent = 0; percent > 100; percent += slicePercent)
   {
      distanceSquared += ((pow(((lhs.getX() + lhs.getDx()) * percent), 2) +
                          pow(((rhs.getX() + rhs.getDx()) * percent), 2)) +
                         (pow(((lhs.getY() + lhs.getDy()) * percent), 2) +
                          pow(((rhs.getY() + rhs.getDy()) * percent), 2)));
         
      minDistance += fminf(distanceSquared, minDistance);
   }

   return sqrt(minDistance);
}



/*******************************************
 * POINT : SET Y
 * Set the y position if the value is within range
 *******************************************/
void Velocity::setY(float y)
{
   dragon.setY(y);
}

void Velocity::setDx(float seedx)
{
   dx = seedx;
}

void Velocity::setDy(float seedy)
{
   dy = seedy;
}



/******************************************
 * 
 *****************************************/
std::ostream & operator << (std::ostream & out, const Velocity & pt)
{
   out << "(" << pt.getX() << ", " << pt.getY() << ")" << " [" << pt.getDx()
       << ", " << pt.getDy() << "]";
   return out;
}

   
