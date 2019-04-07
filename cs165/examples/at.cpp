/*****************************************************
 * File: templates.cpp
 *
 * Purpose: Practice writing function templates.
 *****************************************************/

#include <iostream>
#include <string>

using namespace std;

class Point
{
private:
   int x;
   int y;

public:
   Point() : x(0), y(0) { }
   Point(int x, int y) : x(x), y(y) { }

   int getX() const { return x; }
   int getY() const { return y; }
   void setX(int x) { this->x = x; }
   void setY(int y) { this->y = y; }

   void prompt()
   {
      cout << "Enter x: ";
      cin >> x;

      cout << "Enter y: ";
      cin >> y;
   }

   // TODO: Implement needed operators here.
};

class Scripture
{
private:
   string book;
   int chapter;
   int verse;

public:
   Scripture() : book(""), chapter(-1), verse(-1) { }
   Scripture(string book, int chapter, int verse)
      : book(book), chapter(chapter), verse(verse) { }

   string getBook() const { return book; }
   int getChapter() const { return chapter; }
   int getVerse() const { return verse; }

   void setBook(string book) { this->book = book; }
   void setChapter(int chapter) { this->chapter = chapter; }
   void setVerse(int verse) { this->verse = verse; }

   void prompt()
   {
      cout << "Enter Book: ";
      cin.ignore(256, '\n');
      getline(cin, book);

      cout << "Enter Chapter: ";
      cin >> chapter;

      cout << "Enter Verse: "; 
      cin >> verse;
   }

   // TODO: Implement needed operators here.
};

// TODO: Create search function here

void initializeArrays(int[], Point[], Scripture[]);

int main()
{
   const int ARRAY_SIZE = 3;

   int ints[ARRAY_SIZE];
   Point points[ARRAY_SIZE];
   Scripture scriptures[ARRAY_SIZE];

   initializeArrays(ints, points, scriptures);

   int num;
   cout << "Enter a number: ";
   cin >> num;

   if (/* TODO: call your function here */)
      cout << "In the list.\n";
   else
      cout << "Not in the list.\n";

   Point point;
   point.prompt();

   if (/* TODO: call your function here */)
      cout << "In the list.\n";
   else
      cout << "Not in the list.\n";

   Scripture scripture;
   scripture.prompt();

   if (/* TODO: call your function here */)
      cout << "In the list.\n";
   else
      cout << "Not in the list.\n";

   return 0;
}

void initializeArrays(int ints[], Point points[], Scripture scriptures[])
{
   ints[0] = 1;
   ints[1] = 2;
   ints[2] = 42;

   points[0] = Point(2, 3);
   points[1] = Point(-1, 4);
   points[2] = Point(9, 9);

   scriptures[0] = Scripture("Proverbs", 3, 5);
   scriptures[1] = Scripture("D&C", 112, 10);
   scriptures[2] = Scripture("Matthew", 5, 16);
}

// end-of-file
