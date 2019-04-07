/***********************************************************************
* Program:
*    Assignment ##, ????          (e.g. Assignment 01, Hello World)  
*    Brother {Grimmett, Sloan, Comeau, Neff, Helfrich}, CS124
* Author:
*    your name
* Summary: 
*    Enter a brief description of your program here!  Please note that if
*    you do not take the time to fill out this block, YOU WILL LOSE POINTS.
*    Before you begin working, estimate the time you think it will
*    take you to do the assignment and include it in this header block.
*    Before you submit the assignment include the actual time it took.
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
using namespace std;

struct Address
{
   string street;
   string city;
   char state[3];
   int zip;
};

void prompt(Address & input)
{
   cout << "What is your street adress? ";
   getline(cin, input.street);
   cout << "What is your city? ";
   getline(cin, input.city);
   cout << "What is your state and zip? ";
   cin >> input.state >> input.zip;
}


void display(const Address & output)
{
   cout << output.street << endl
        << output.city << ", "
        << output.state << " "
        << output.zip << endl;
}

/**********************************************************************
 * Add text here to describe what the function "main" does. Also don't forget
 * to fill this out with meaningful text or YOU WILL LOSE POINTS.
 ***********************************************************************/
int main()
{
   Address Address;

   prompt(Address);

   display(Address);

   return 0;
}
