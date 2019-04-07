/***********************************************************************
* Program:
*    Assignment 34, Polymorphism
*    Brother Comeau, CS165
* Author:
*    Keith Wheeler
* Summary: 
*    This assignment is to demonstrate polymorphism.  The goal is
*    to create an 8x8 array of pieces representing a chess board
*    and to display them on the screen.
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
   virtual char getLetter() const         { return ' ';     }
protected:
   bool isWhite;
};

class King : public Piece
{
public:
   King(bool isWhite) : Piece(isWhite), score(0) {}
   int getScore()
   {
      if (isWhite)
         return 100;
      else
         return -100;
   }
   char getLetter() const
   {
      if (isWhite)
         return 'k';
      else
         return 'K';
   }
private:
   int score;
};

class Queen : public Piece
{
public:
    Queen(bool isWhite) : Piece(isWhite), score(0) {}
   int getScore()
   {
      if (isWhite)
         return 10;
      else
         return -10;
   }
   char getLetter() const
   {
      if (isWhite)
         return 'q';
      else
         return 'Q';
   }
private:
   int score;
};

class Pawn : public Piece
{
public:
    Pawn(bool isWhite) : Piece(isWhite), score(0) {}
   int getScore()
   {
      if (isWhite)
         return 1;
      else
         return -1;
   }
   char getLetter() const
   {
      if (isWhite)
         return 'p';
      else
         return 'P';
   }
private:
   int score;
};

class Rook : public Piece
{
public:
   Rook(bool isWhite) : Piece(isWhite), score(0) {}
   int getScore()
   {
      if (isWhite)
         return 1;
      else
         return -1;
   }
   char getLetter() const
   {
      if (isWhite)
         return 'r';
      else
         return 'R';
   }
private:
   int score;
};

class Knight : public Piece
{
public:
   Knight(bool isWhite) : Piece(isWhite), score(0) {}
   int getScore()
   {
      if (isWhite)
         return 1;
      else
         return -1;
   }
   char getLetter() const
   {
      if (isWhite)
         return 'n';
      else
         return 'N';
   }
private:
   int score;
};

class Bishop : public Piece
{
public:
   Bishop(bool isWhite) : Piece(isWhite), score(0) {}
   int getScore()
   {
      if (isWhite)
         return 1;
      else
         return -1;
   }
   char getLetter() const
   {
      if (isWhite)
         return 'b';
      else
         return 'B';
   }
private:
   int score;
};

/*********************************************
 * OUT << PIECE
 * Insertion operator for the piece
 ********************************************/
ostream & operator << (ostream & out, const Piece & rhs)
{
   out << rhs.getLetter();
   return out;
}

/**********************************************************************
 * MAIN: This is a driver program for our various piece classes.
 *       You are not allowed to change MAIN in any way
 ***********************************************************************/
int main()
{
   // make an array of pieces
   Piece * board[8][8];

   // the white army
   board[0][0] = new Rook  (true /*white*/);
   board[0][1] = new Knight(true /*white*/);
   board[0][2] = new Bishop(true /*white*/);
   board[0][3] = new Queen (true /*white*/);
   board[0][4] = new King  (true /*white*/);
   board[0][5] = new Bishop(true /*white*/);
   board[0][6] = new Knight(true /*white*/);
   board[0][7] = new Rook  (true /*white*/);

   // the pawns
   for (int col = 0; col < 8; col++)
   {
      board[1][col] = new Pawn  (true  /*white*/);
      board[6][col] = new Pawn  (false /*black*/);      
   }

   // the spaces
   for (int row = 2; row < 6; row++)
      for (int col = 0; col < 8; col++)
         board[row][col] = new Piece(true);
   
   // the black army
   board[7][0] = new Rook  (false /*black*/);
   board[7][1] = new Knight(false /*black*/);
   board[7][2] = new Bishop(false /*black*/);
   board[7][3] = new Queen (false /*black*/);
   board[7][4] = new King  (false /*black*/);
   board[7][5] = new Bishop(false /*black*/);
   board[7][6] = new Knight(false /*black*/);
   board[7][7] = new Rook  (false /*black*/);

   // display the board
   for (int row = 7; row >= 0; row--)
   {
      for (int col = 0; col < 8; col++)
         cout << *board[row][col];
      cout << endl;
   }

   // destroy everything
   for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
         delete board[row][col];

   return 0;
}
