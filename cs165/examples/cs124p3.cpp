/***********************************************************************
* Program:
*				Project 3, Mad Lib files													
*				Brother Burton, CS124
* Author:
*				Keith Wheeler
* Summary:		
*			This program will prompt the user for the mad lib file
*			and then prompt for the information and then replace and
*			display the results
*				
*				
*
*				Estimated:		0.0 hrs				
*				Actual:					0.0 hrs
*						
************************************************************************/
#include <fstream>
#include <iostream>
using namespace std;
/********************************************
* getFileName will ask for the fileName
* of the mad lib
**********************************************/
void getFileName(char fileName[])
{
			cout << "Please enter the filename of the Mad Lib: ";
			cin >> fileName;
}
/**********************************************
* getUserArray will replace some of the txt in
* the array with user input
************************************************/
void getUserArray(char mad[][256], int size)
{
   cin.ignore();
   for (int i = 0; i < size; i++)
      if (mad[i][0] == '<')
         switch (mad[i][1])
         {
            case '#':
               mad[i][0] = '\n';
               mad[i][1] = 0;
               break;
            case '[':
               mad[i][0] = ' ';
               mad[i][1] = '\'';
               mad[i][2] = 0;
               break;
            case ']':
               mad[i][0] = '\'';
               mad[i][1] = ' ';
               mad[i][2] = 0;
               break;
            case '{':
               mad[i][0] = ' ';
               mad[i][1] = '"';
               mad[i][2] = 0;
               break;
            case '}':
               mad[i][0] = '"';
               mad[i][1] = ' ';
               mad[i][2] = 0;
               break;
            default:
               int j;
               for (j = 1; mad[i][j]; j++)
               {
                  if (mad[i][j] == '_')
                     mad[i][j - 1] = ' ';
                  else if (mad[i][j] == '>')
                  {
                     mad[i][j] = 0;
                     mad[i][j - 1] = ':';
                  }
                  else
                     mad[i][j - 1] = mad[i][j];
               }
               mad[i][0] = toupper(mad[i][0]);
															cout << "\t" << mad[i] << " ";
															cin.getline(mad[i], 256);
         }
}
/******************************************** * displayMad will show the array
 *       *********************************************/
void displayMad(char mad[][256], int size) 
{
   cout << "\n";
   for (int i = 0; i < size; i++)
   {
      cout << mad[i];
						if ( *mad[i + 1] == '.' || *mad[i + 1] == '!' ||
                                                     *mad[i + 1] == '?' || *mad[i + 1] == ',' ||
                                                     *mad[i] == '\n' || *mad[i + 1] == '\n' ||
                                                     *mad[i] == '"' || *mad[i] == ' \'' ||
                                                     *mad[i + 1] == '\'' || *mad[i - 1] == '\'');
						else
                                                   cout << " ";
   }
   cout << endl; 
}
/************************************************* * readFile will put the mad lib into the array
**************************************************/
void readFile(char fileName[], char mad[][256]) {
   ifstream fin;
   fin.open(fileName);
   if (fin.fail())
   {
      cout << "Could not open '" << fileName
           << "'.\n";
   }
   int i = 0;
   while (fin >> mad[i])
      i++;
   
   fin.close();
   getUserArray(mad, i);
   displayMad(mad, i);
}
/***************************************
* replay will ask the user if they want
*        to play again
*****************************************/
bool replay()
{
   char replay;
   cout << "Do you want to play again (y/n)? ";
   cin >> replay;
   if (replay == 'y')
      return true;
   else
      return false;
}
/**********************************************************************
* main will call all the other functions
* and drive the program to victory
***********************************************************************/
int main()
{
   char fileName[256];
   getFileName(fileName);
   char mad[256][256];
   readFile(fileName, mad);
   while (replay())
   {
      getFileName(fileName);
      readFile(fileName, mad);
   }
   cout << "Thank you for playing.\n";
   
   
   return 0;
}
