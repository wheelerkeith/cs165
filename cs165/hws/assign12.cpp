/***********************************************************************
* Program:
*    Assignment 12, Exception Handling
*    Brother Comeau, CS165
* Author:
*    Keith Wheeler
* Summary: 
*    This program is designed to illustrate the types of information that
*    we can send through the exception handling mechanism.
*
*    Estimated:  1.0 hrs   
*    Actual:     2.0 hrs
*      Catching all thrown ints
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/***********************************************************
 * READ DATA: Read the data from a file
 *   INPUT:  fileName. the file to be read
 *   OUTPUT: data.  The data from the file
 * IMPORTANT: You are not allowed to change readData() in any way
 ***********************************************************/
string readData(const string & fileName) throw (string, bool, int)
{
   // missing file case
   if (fileName.size() == 0)
      throw true;             // "ERROR: No filename specified\n"

   // attempt to open the file
   ifstream fin(fileName.c_str());
   if (fin.fail())
      throw fileName;         //  "ERROR: Invalid filename \"" << s << "\"\n"

   // attempt to read the data
   string data;
   getline(fin, data);
   bool moreData = !fin.eof();
   fin.close();

   // empty file
   if (data.size() == 0)
      throw 0;                // "ERROR: The file was empty\n"

   // message too long
   if (data.size() > 140)
      throw 1;                // "ERROR: The message exceeded 140 characters\n"

   // more than one line of data
   if (moreData)
      throw 2;                // "ERROR: The message was longer than 1 line\n"

   // success
   return data;
}

/**********************************************************************
 * MAIN: This function will prompt the user for the file and display the
 *       contents on the screen.
 ***********************************************************************/
int main()
{
   // get the filename
   string fileName;
   cout << "What is the filename? ";
   getline(cin, fileName);

   try
   {
      readData(fileName);
   }

   catch (bool)
   {
      cout << "ERROR: No filename specified\n";
   }

   catch (string fileName)
   {
      string s = fileName;
      cout << "ERROR: Invalid filename \"" << s << "\"\n";
   }

   catch (int e)
   {
      if (e == 0)
         cout << "ERROR: The file was empty\n";
      else if (e == 1)
         cout << "ERROR: The message exceeded 140 characters\n";
      else if (e == 2)
         cout << "ERROR: The message was longer than 1 line\n";
   }
   
   // read the data
   string data = readData(fileName);

   // display the results:
   cout << "The important fact: \""
        << data
        << "\"\n";
   
   return 0;
}
