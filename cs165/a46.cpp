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
   string word;
   while (!fin.eof())
   {
      fin >> word;
      alaska.push_back(word);
   }
   fin.close();

   for (auto wee = alaska.rbegin(); wee != alaska.rend(); ++wee)
      cout << *wee;
   cout << endl;

   return 0;
}