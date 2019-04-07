/***********************************************************************
 * Source File:
 *    Path: A point in motion
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a point in motion, including
 *    Path addition (additive vectors) and subtraction (distance)
 ************************************************************************/

#include "path.h"
#include <cassert>
#include <cmath>
#include <limits>

/**************************************
 * Path : Equality
 ************************************/
bool Path::operator == (const Path & rhs)
{
   return rhs.getX() == getX() &&
      rhs.getY() == getY() &&
      rhs.getDx() == getDx() &&
      rhs.getDy() == getDy();
}

/****************************************
 * Path : ASSIGNMENT
 ****************************************/
const Path & Path::operator = (const Path & rhs)
{
   setX(rhs.getX());
   setY(rhs.getY());
   setDx(rhs.getDx());
   setDy(rhs.getDy());
   setWrap(rhs.getWrap());
   setCheck(rhs.getCheck());
   
   return *this;
}

/****************************************
 * Path : ASSIGNMENT
 ****************************************/
const Path & Path::operator = (const Point & rhs)
{
   setX(rhs.getX());
   setY(rhs.getY());
   setWrap(rhs.getWrap());
   setCheck(rhs.getCheck());
   
   return *this;
}


/***************************************
 * Path : GET POINT
 * Fetch the point out of a vector
 ***************************************/
Point Path::getPoint() const
{
   Point point(getX(), getY());
   point.setCheck(getCheck());
   return point;
}

/************************************
 * Path : SET MAG
 * Set the speed or magnitude of the velocity
 ***********************************/
void Path::setMag(float speed)
{
   float angleRadians = deg2rad(getAngle());
   dx = -cos(angleRadians) * speed;
   dy = -sin(angleRadians) * speed;
}

/**********************************
 * Path : SET ANGLE
 * Set the angle of the current velocity
 *********************************/
void Path::setAngle(float angleDegrees)
{
   float angleRadians = deg2rad(angleDegrees);
   float speed = getMag();
   dx = -cos(angleRadians) * speed;
   dy = -sin(angleRadians) * speed;
}

/**************************************
 * Path : SET VELOCITY
 *          Set Dx and Dy for the vector
 * INPUT angleDegrees : new angle in degrees
 *       speed        : magnitude of the vecotr
 **************************************/
void Path::setVelocity(float angleDegrees, float speed)
{
   float angleRadians = deg2rad(angleDegrees);
   dx = -cos(angleRadians) * speed;
   dy = -sin(angleRadians) * speed;
}


/***************************************
 * Path : POSTFIX INCREMENT
 * Advance the Path by one time unit
 **************************************/
Path Path::operator ++ (int postfix)
{
   Path v = *this;
   addX(dx);
   addY(dy);
   return v;
}

/***************************************
 * Path : PREFIX INCREMENT
 * Advance the Path by one time unit
 **************************************/
Path & Path::operator ++ ()
{
   addX(dx);
   addY(dy);
   return *this;
}

/**************************************
 * Path : ADDITION
 * Add two vectors
 *************************************/
Path Path::operator + (const Path & rhs) const
{
   Path vReturn(*this);
   vReturn += rhs;
   return vReturn;
}

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))


/**************************************
 * Path : SUBTRACTION
 * Find the minimal distance between two vectors
 *************************************/
float Path::operator - (const Path & vRhs) const
{
   // find the maximum distance traveled
   using std::abs;
   float dMax = MAX(abs(dx), abs(dy));
   dMax = MAX(dMax, abs(vRhs.getDx()));
   dMax = MAX(dMax, abs(vRhs.getDy()));
   dMax = MAX(dMax, (float)0.1); // when dx and dy are 0.0. Go through the loop once.
   
   // we will advance by this number
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point pointLhs(     getX() + (dx * i / dMax),
                          getY() + (dy * i / dMax));
      Point pointRhs(vRhs.getX() + (vRhs.getDx() * i / dMax),
                     vRhs.getY() + (vRhs.getDy() * i / dMax));
      
      float distSquared =
         ((pointLhs.getX() - pointRhs.getX()) *
          (pointLhs.getX() - pointRhs.getX())) +
         ((pointLhs.getY() - pointRhs.getY()) *
          (pointLhs.getY() - pointRhs.getY()));
      distMin = MIN(distMin, distSquared);
   }
   
   return sqrt(distMin);
}


/**********************************************
 * Path +=
 *        Add the dx, dy of the rhs onto the current
 *        Vector
 *********************************************/
Path & Path::operator += ( const Path & rhs)
{
   dx += rhs.getDx();
   dy += rhs.getDy();
   return *this;
}

/******************************************
 * Path insertion
 *       Display a Path on the screen
 *****************************************/
std::ostream & operator << (std::ostream & out, const Path & v)
{
   out << v.getPoint()
       << " [" << v.getDx() << ", " << v.getDy() << "]";
   return out;
}

/*******************************************
 * Path extraction
 *        Prompt for Path coordinates
 ******************************************/
std::istream & operator >> (std::istream & in, Path & v)
{
   float x;
   float y;
   float dx;
   float dy;
   in >> x >> y >> dx >> dy;

   v.setX(x);
   v.setY(y);
   v.setDx(dx);
   v.setDy(dy);
   
   return in;
}
