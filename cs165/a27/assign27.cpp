/***********************************************************************
* Program:
*    Assignment 27, Velocity class
*    Brother {Burton, Helfrich, Comeau}, CS165
* Author:
*    your name
* Summary: 
*    This is a driver program for cs165 assignment 2.7
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <iomanip>
#include "velocity.h"
#include "point.h"
using namespace std;

// Point class static variables
float Point::xMin = -200;
float Point::xMax = 200;
float Point::yMin = -200;
float Point::yMax = 200;

/**********************************************************************
 * Prompt the user for velocity values
 *********************************************************************/
void promptVelocity(string promptMessage, Velocity &vel)
{
   cout << promptMessage << endl;

   float x;
   float y;
   cout << "  Enter x and y: ";
   cin >> x >> y;

   float dx;
   float dy;
   cout << "  Enter dx and dy: ";
   cin >> dx >> dy;

   vel.setX(x);
   vel.setY(y);
   vel.setDx(dx);
   vel.setDy(dy);
}

/**********************************************************************
 * Driver program for CS165 assign 2.6
 ***********************************************************************/
int main()
{
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(3);

   // variables for testing
   Velocity v1;
   Velocity v2;
   float scalar = 0.0;

   // Prompt for velocity values
   promptVelocity("Enter values for Velocity 1", v1);
   promptVelocity("Enter values for Velocity 2", v2);
   
   cout << "Enter float scalar value: ";
   cin >> scalar;

   // Test operator >
   //   cout << "Testing Operator >\n";
   cout << v1 << " > " << scalar 
	<< " is "
	<< ((v1 > scalar) ? "true" : "false" )
	<< endl;

   // Test operator <
   //cout << "Testing Operator <\n";
   cout << v1 << " < " << scalar 
	<< " is "
	<< ((v1 < scalar) ? "true" : "false" )
	<< endl;

   // Test operator >=
   //cout << "Testing Operator >=\n";
   cout << v1 << " >= " << scalar 
	<< " is "
	<< ((v1 >= scalar) ? "true" : "false" )
	<< endl;

   // Test operator <=
   //cout << "Testing Operator <=\n";
   cout << v1 << " <= " << scalar 
	<< " is "
	<< ((v1 <= scalar) ? "true" : "false" )
	<< endl;

   // Test operator -
   cout << v1 << " - " << v2 
	<< " is "
	<< (v1 - v2)
	<< endl;

   return 0;
}
