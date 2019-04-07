/***********************************************************************
 * This program is designed to demonstrate:
 *      This program will demonstrate how to define a structure, declare a
 *      variable, reference the member variables, and pass a structure as
 *      a parameter
 ************************************************************************/

#include <iostream>
using namespace std;

/******************************************
 * ADDRESS
 * A standard address such as y ou would
 * find on an envelope
 *****************************************/
struct Address
{
   string street;     // the street can be long, use the string class
   string city;       // same is true with the city
   char state[3];     // states use a two-letter abbreviation, plus \0
   int zip;           // the zip is a five digit integer
};

// fill the Address structure
void prompt(Address & input);

// display the contents of the address on the screen
void display(const Address & output);

/**********************************************************************
* This will be just a simple driver program 
***********************************************************************/
int main()
{
   Address address;    // declare the variable
   prompt (address);   // since it is pass-by-reference, address changes
   display(address);   // since it is a const, address cannot change
   return 0;
}

/**************************************
 * PROMPT
 * Prompt the user for an address
 ***************************************/
void prompt(Address & input)               
{
   cout << "What is your street address? ";
   getline(cin, input.street);
   cout << "What is your city? ";
   getline(cin, input.city);
   cout << "What is your state and zip? ";
   cin  >> input.state >> input.zip;
}

/*************************************
 * DISPLAY
 * Display the contents of the address
 **************************************/
void display(const Address & output)
{
   cout << output.street << endl
        << output.city   << ", "
        << output.state  << " "
        << output.zip    << endl;
}
