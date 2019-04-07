#include <iostream>
#include <fstream>
using namespace std;


void display(char board[][3])
{
   for (int h = 0; h < 3; h++)
   {
      for (int k = 0; k < 3; k++)
      {
         cout << board[h][k];
      }
      cout << endl;
   }
}

void readFile()
{
   char board[3][3];
   
   char filename[256];
   cout << "Enter source filename: ";
   cin >> filename;
   
   ifstream fin;
   fin.open(filename);
   for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
         fin >> board[i][j];
         
   display(board);
   
}

int main()
{

   readFile();
   return 0;
}