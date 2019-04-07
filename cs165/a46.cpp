/***********************************************************************
* Program:
*    Assignment 46, Standard Libraries
*    Brother Comeau, CS165
* Author:
*    Keith Wheeler
* Summary: 
*    A class template is similar to a function template, except the
*    abstract type can be applied to all member functions and all
*    member variables of the class. Your job with this assignment is
*    to convert the following class to be type-agnostic.
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part
************************************************************************/
#include <deque>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
   deque <string> alaska;
   string filename;

   cout << "Enter the name of the file: ";
   cin >> filename;

   ifstream fin;
   fin.open(filename.c_str());
   if (fin.fail())
      cout << "Cannot open file";
   else
   {
   
      string word;
      while (true)
      {
         if (fin.eof())
            break;
         getline(fin, word);
         alaska.push_front(word);
      }
      fin.close();
      
      for (deque <string>::iterator wee = alaska.begin(); wee != alaska.end(); wee++)
      {
         if(wee == alaska.begin())
            cout << *wee;
         else
            cout << *wee << endl;
      }
   }
   
   return 0;
}
