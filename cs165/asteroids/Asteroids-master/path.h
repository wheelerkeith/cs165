/***********************************************************************
 * Header File:
 *    Vector: A point in motion
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a point in motion, including
 *    vector addition (additive vectors) and subtraction (distance)
 ************************************************************************/


#ifndef PATH_H
#define PATH_H

#define _USE_MATH_DEFINES
#include <cmath>      // for M_PI, sin() and cos()
#include <math.h>     // the Windows version of the same
#include <iostream>   // for ISTREAM and OSTREAEM
#include "point.h"


#define deg2rad(value) ((double)((M_PI / 180.0) * (value)))
#define rad2deg(value) ((double)((value) * (180.0 / M_PI)))

/*******************************************
 * Path
 * A point, plus angle, plus magnitude
 ******************************************/
class Path : public Point
{
public:
   // constructors
   Path(int objectX, int objectY) :   Point(objectX, objectY), dx(0.0), dy(0.0) {              }
   Path(const Path &rhs)                     { *this = rhs; }
   Path(const Point &rhs) : dx(0.0), dy(0.0) { *this = rhs; }

   // getters
   Point getPoint() const;
   double getDx()    const { return dx;                      }
   double getDy()    const { return dy;                      }
   double getMag()   const { return sqrt(dx * dx + dy * dy); }
   double getAngle() const { return (double)rad2deg(atan2(-dy, dx)); }

   // setters
   void setDx(double dx)     { this->dx = dx; }
   void setDy(double dy)     { this->dy = dy; }
   void setMag(double mag);
   void setAngle(double angle);
   void setVelocity(double angleDegrees, double speed);

   // arithemetic 
   Path   operator ++ (int postfix);
   Path & operator ++ ();       
   double    operator -  (const Path &rhs) const;   // minimum distance
   Path   operator +  (const Path &rhs) const;   // Path addition
   Path & operator += ( const Path & rhs);

   // comparision
   bool operator == (const Path & rhs);

   // assignment
   const Path & operator = (const Path & rhs);
   const Path & operator = (const Point & rhs);
   
private:
   double dx;
   double dy;
};

// for debug purposes
std::ostream & operator << (std::ostream & out, const Path & v);
std::istream & operator >> (std::istream & in,        Path & v);

#endif // Path_H
