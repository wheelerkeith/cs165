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
#define MAX(a, b) ((a) < (b) ? (b) : (a));
#define MIN(a, b) ((a) > (b) ? (b) : (a));

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

double operator - (const Velocity &lhs, const Velocity &rhs)
{
   double slice = fmax(fabs(lhs.dx), fabs(lhs.dy));
   slice = fmax(slice, fabs(rhs.dx));
   slice = fmax(slice, fabs(rhs.dy));
   slice = 1 / slice;

   double minDistance = 100000000;

   for (double percent = 0; percent < 1; percent += slice)
   {
      double xvalue = (lhs.getX() + lhs.dx * percent) - (rhs.getX() + rhs.dx * percent);
      double yvalue = (lhs.getY() + lhs.dy * percent) - (rhs.getY() + rhs.dy * percent);
      double dist = (xvalue * xvalue) + (yvalue * yvalue);
      minDistance = fmin(minDistance, dist);
   }

   return sqrt(minDistance);
}

void Velocity :: operator = (const Velocity & rhs)
{
   this->setX(rhs.getX());
   this->setY(rhs.getY());
   this->dx = rhs.dx;
   this->dy = rhs.dy;
}

Velocity Velocity :: operator + (const Velocity & v2)
{
   Velocity beard;

   beard.setX(this->getX());
   beard.setY(this->getY());
   beard.setDx(this->getDx() + v2.dx);
   beard.setDy(this->getDy() + v2.dy);

   return beard;
}

void Velocity :: operator += (Velocity & v2)
{
   this->setDx(this->dx + v2.dx);
   this->setDy(this->dy + v2.dy);
}

void Velocity :: operator ++ (int postfix)
{
   this->setX(this->dx + this->getX());
   this->setY(this->dy + this->getY());
}

void Velocity :: operator ++ ()
{
   this->setX(this->dx + this->getX());
   this->setY(this->dy + this->getY());
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

   
