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
   virtual char getLetter() const
   {
      if (
   }
protected:
   bool isWhite;
};



class Rook : public Piece
{
public:
   Rook(bool isWhite) : Piece(isWhite), score(0) {};
   int getScore()
   {
      if (isWhite)
         return 1;
      else
         return -1;
   };
   char getLetter()
   {
      if (isWhite)
         return 'r';
      else
         return 'R';
   };
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

int main()
{
   Piece * board[0][0];

   board[0][0] = new Rook  (true /*white*/);

   cout << *board[0][0] << endl;


   // destroy everything
   delete board[0][0];

   return 0;
}
