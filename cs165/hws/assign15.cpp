/***********************************************************************
* Program:
*    Assignment 15, Overloading Coordinate
*    Brother Comeau, CS165
* Author:
*    Keith Wheeler
* Summary: 
*    This program will test several ways to initialize a Position structure
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part
************************************************************************/

#include <iostream>
using namespace std;

/**************************************
 * COORDINATE
 * A chess board coordinate
 *************************************/
struct Coordinate
{
   int row;
   int col;
};

/***************************************************
 * replaces the zeros with row and col in coordl
 **************************************************/
inline void initialize(Coordinate & coord1, int row = 0, int col = 0)
{
   coord1.row = row;
   coord1.col = col;
}

/****************************
 * Copies coordl to coord2
 ***************************/
void initialize(Coordinate & coord2, Coordinate & coord1)
{
   coord2 = coord1;
}

/**********************************************************************
 * MAIN
 * This driver program will just exercise the several different
 * versions of initialize().
 *
 * You are not allowed to change main() in any way.
 ***********************************************************************/
int main()
{
   // initialize with one parameter: set to (0, 0)
   Coordinate coord1;
   initialize(coord1);
   cout << "Initial value of coord1 is: ("
        << coord1.col << ", " << coord1.row << ")\n";

   // now prompt the user for the values
   int row;
   int col;
   cout << "What is the new value of row, col? ";
   cin  >> col >> row;
   initialize(coord1, row, col);
   cout << "New value of coord1 is: ("
        << coord1.col << ", " << coord1.row << ")\n";

   // now we will copy coord1 into coord2
   Coordinate coord2;
   initialize(coord2, coord1);
   cout << "The value of coord2 after copy is: ("
        << coord2.col << ", " << coord2.row << ")\n";
   
   return 0;
}
