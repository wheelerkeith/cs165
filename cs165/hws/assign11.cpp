/***********************************************************************
* Program:
*    Assignment 11, Defensive Programming
*    Brother Comeau, CS165
* Author:
*    Keith Wheeler
* Summary: 
*    Write a function to accept two integer values from the user.  This
*    function must be resistant to all user-induced errors.
*
*    Estimated:  0.5 hrs   
*    Actual:     1.0 hrs
*      The output of col and row.
************************************************************************/

#include <iostream>
#include <cassert>
using namespace std;

/***********************************************************************
 * GET COORDINATES
 * Prompt the user for a row and column
 ***********************************************************************/
void getCoordinates(int & col, int & row)
{
   cout << "Please enter a row and column where both are integers\n"
        << "> ";

   cin >> col >> row;

   if (cin.fail())
   {
      do
      {
         cout << "ERROR: non-digit entered\n";
         cin.clear();
         cin.ignore(256, '\n');

         cout << "> ";
         cin >> col >> row;
      }
      while (cin.fail());
   }
}

/***********************************************************************
 * Simple driver program for getCoordinate
 ***********************************************************************/
int main()
{
   int col;
   int row;

   getCoordinates(col, row);

   cout << "The values are: ("
        << col << ", " << row << ")\n";
   
   return 0;
}
