/***********************************************************************
* Program:
*    Assignment 45, Iterators
*    Brother Comeau, CS165
* Author:
*    Keith Wheeler
* Summary: 
*    This program is designed to demonstrate using iterators to walk
*    through a container or collection of elements.
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part
************************************************************************/

#include <iostream>
#include <string>
using namespace std;

/**********************************************************************
 * Instructions: Please fill in the code below the comments to demonstrate
 * three ways to walk through a string object
 ***********************************************************************/
int main()
{
   // fetch the text
   string text;
   cout << "What is the text: ";
   getline(cin, text);

   // display the text using the array notation
   cout << "Array:    ";
   for (unsigned i = 0; i < text.size(); i++)
       cout << text[i];
   cout << endl;
   
   // display the text using the pointer notation
   cout << "Pointers: ";
   for (const char *t = text.c_str(); *t != '\0'; t++)
      cout << *t;
   cout << endl;

   // display the text using the iterator notation
   cout << "Iterator: ";
   for (string::iterator t = text.begin(); t != text.end(); t++)
      cout << *t;
   cout << endl;
   
   return 0;
}
