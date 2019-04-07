#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void readfile(int board[][9])
{
   string filename;
   cout << "Filename? :";
   cin >> filename;

   fstream fin(filename.c_str());
   for (int i = 0; i <= 9; i++)
      for (int j = 0; j <= 9; j++)
      {
         fin >> board[i][j];
         cout << fin;
      }
}

void display(int board[][9])
{
   for (int i = 0; i <= 9; i++)
   {
      cout << endl;
      for (int j = 0; j <= 9; j++)
      {
         cout << board[i][j];
      }
   }
}

void interact()
{
   int board[9][9];
   readfile(board);

   display(board);
}

int main()
{
   interact();
   
   return 0;
}
