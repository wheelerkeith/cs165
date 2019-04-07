/***********************************************************************
* Program:
*    Assignment 32, Simple Inheritance
*    Brother Comeau, CS165
* Author:
*    Keith Wheeler
* Summary: 
*    This program will demonstrate the implementation of simple
*    inheritance
*
*    Your assignment is to create three derrived classes from our
*    Piece class.  They will function exactly the same as the
*    Piece structures we created from Assignment 3.1
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part
************************************************************************/

#include <iostream>
#include <cassert>
using namespace std;

/*****************************************
 * PIECE
 * The base piece class.  You are not allowed
 * to change the definition of Piece in any way
 *****************************************/
class Piece
{
public:
   Piece(bool isWhite) : isWhite(isWhite) {                 }
   bool getIsWhite() const                { return isWhite; }
   char getLetter() const                 { return ' ';     }
private:
   bool isWhite;
};

class King : public Piece
{
public:
   King(bool isWhite) : Piece(isWhite), score(0) {};
   int getScore()
   {
      if (getIsWhite())
         return 100;
      else
         return -100;
   };
   char getLetter()
   {
      if (getIsWhite())
         return 'k';
      else
         return 'K';
   };
private:
   int score;
};

class Queen : public Piece
{
public:
    Queen(bool isWhite) : Piece(isWhite), score(0) {};
   int getScore()
   {
      if (getIsWhite())
         return 10;
      else
         return -10;
   };
    char getLetter()
   {
      if (getIsWhite())
         return 'q';
      else
         return 'Q';
   };
private:
   int score;
};

class Pawn : public Piece
{
public:
    Pawn(bool isWhite) : Piece(isWhite), score(0) {};
   int getScore()
   {
      if (getIsWhite())
         return 1;
      else
         return -1;
   };
    char getLetter()
   {
      if (getIsWhite())
         return 'p';
      else
         return 'P';
   };
private:
   int score;
};

/**********************************************************************
 * MAIN is designed to use our home-made class called Piece.  You are not
 *   allowed to change the definition of Date nor modify any code in MAIN
 ***********************************************************************/
int main()
{
   // first test our base class
   Piece piece(false);
   cout << "The piece is a space: '" << piece.getLetter()      << "'\n\n";
   // we cannot call piece.getScore() because
   // that is only in the derrived classes
   
   // next test the King
   King kingWhite(true /*white*/);
   cout << "The white King:       '"
        << kingWhite.getLetter()  << "' points:"
        << kingWhite.getScore()   << "\n";
   King kingBlack(false /*white*/);
   cout << "The black King:       '"
        << kingBlack.getLetter()  << "' points:"
        << kingBlack.getScore()   << "\n";
   
   // next test the Queen
   Queen queenWhite(true /*white*/);
   cout << "The white Queen:      '"
        << queenWhite.getLetter()  << "' points:"
        << queenWhite.getScore()   << "\n";
   Queen queenBlack(false /*white*/);
   cout << "The black Queen:      '"
        << queenBlack.getLetter()  << "' points:"
        << queenBlack.getScore()   << "\n";

   // finally test the Pawn
   Pawn pawnWhite(true /*white*/);
   cout << "The white Pawn:       '"
        << pawnWhite.getLetter()  << "' points:"
        << pawnWhite.getScore()   << "\n";
   Pawn pawnBlack(false /*white*/);
   cout << "The black Pawn:       '"
        << pawnBlack.getLetter()  << "' points:"
        << pawnBlack.getScore()   << "\n";

   return 0;
}
