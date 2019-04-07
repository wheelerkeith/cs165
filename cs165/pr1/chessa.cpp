/***********************************************************************
 * Program:
 *    Project 1, Procedural Chess
 *    Brother Comeau, CS165
 * Author:
 *    Keith Wheeler
 * Summary:
 *    This program will let two users play a game of chess
 ************************************************************************/

#include <string>      // string class used throughout
#include <cassert>     // for asserts
#include <iostream>    // for CIN and COUT
#include <fstream>
using namespace std;

#define NO_PIECE '*'   // There is no piece on this location of the board
#define INVALID 127    // invalid row or column value


/********************************************
 * COORD
 * A single r,c coordinate
 * Written by Br. Helfrich
 *******************************************/
struct Coord
{
   char r;   // row, from 0..7
   char c;   // col, from 0..7
};

/*********************************************
 * MOVE
 * A single move, including the textual description
 * and what it breaks down to
 * Written by Br. Helfrich
 ********************************************/
struct Move
{
   string text;           // textual description of the move
   char   piece;          // unknown piece
   bool   capture;        // did a capture happen this move?
   Coord  source;         // where the move originated from
   Coord  dest;           // where the move finished
   bool   enpassant;      // Enpassant pawn capture
   bool   castleK;        // kingside castle
   bool   castleQ;        // queenside castle
   bool   promote;        // promote to move.piece
};


/**************************************************************
 * MOVE PARSE
 * Accept the user's input in algebra notation and determine
 * if it is valid
 *    INPUT  move.text    The Smith Notation of the move
 *           board[][]    The current state of the board
 *    OUTPUT move.*       All the fields of the move filled in
 *           EXCEPTION    String of error message
 * Written by Br. Helfrich
 *************************************************************/
void moveParse(Move & move, char board[][8]) throw(string)
{
   // initialize the move.  What we know up to this point is... nothing!
   move.piece     = NO_PIECE;
   move.capture   = false;
   move.source.r  = INVALID;
   move.source.c  = INVALID;
   move.dest.r    = INVALID;
   move.dest.c    = INVALID;
   move.enpassant = false;
   move.castleK   = false;
   move.castleQ   = false;
   move.promote   = false;

   //
   // from square
   //

   // column: a-h
   if (move.text[0] < 'a' || move.text[0] > 'h')
      throw string("Invalid format of source coordinates");
   move.source.c = move.text[0] - 'a';
   assert(move.source.c >= 0 && move.source.c <= 7);

   // row: 1-8
   if (move.text[1] < '1' || move.text[1] > '8')
      throw string("Invalid format of source coordinates");
   move.source.r = move.text[1] - '1';
   assert(move.source.r >= 0 && move.source.r <= 7);

   // if there is nothing to move, we have an error
   move.piece = tolower(board[move.source.r][move.source.c]);
   if (move.piece == NO_PIECE)
      throw string("No piece in the source coordinates position");

   //
   // to square
   //
   
   // column: a-h
   if (move.text[2] < 'a' || move.text[2] > 'h')
      throw string("Invalid format of destination coordinates");
   move.dest.c = move.text[2] - 'a';
   assert(move.dest.c >= 0 && move.dest.c <= 7);

   // row: 1-8
   if (move.text[3] < '1' || move.text[3] > '8')
      throw string("Invalid format of destination coordinates");
   move.dest.r = move.text[3] - '1';
   assert(move.dest.r >= 0 && move.dest.r <= 7);

   // capture if there is something there
   if (board[move.dest.r][move.dest.c] != NO_PIECE)
      move.capture = true;

   //
   // capture and promotion
   //

   for (int i = 4; i < move.text.size(); i++)
   {
      switch(move.text[i])
      {
         case 'p':   // capture a pawn
         case 'n':   // capture a knight
         case 'b':   // capture a bishop
         case 'r':   // capture a rook
         case 'q':   // capture a queen
         case 'k':   // !! you can't capture a king you silly!
            move.capture = true;
         break;

         case 'c':  // short castling or kings castle
            move.castleK = true;
            break;
         case 'C':  // long castling or queen castle
            move.castleQ = true;
            break;
         case 'E':  // En-passant
            move.enpassant = true;
            break;

         case 'N':  // Promote to knight
         case 'B':  // Promote to Bishop
         case 'R':  // Promote to Rook
         case 'Q':  // Promote to Queen
            move.piece = tolower(move.text[i]);
         move.promote = true;
         break;

         default:
            // unknown piece
            throw string("Unknown promotion piece specification");
      }
   }

   // if we made it this far, we are successful
   return;
}

/**********************************************************************
 * MOVE: Driver function
 ***********************************************************************/
int moveDriver(char board[][8], string moves)
{
   // forever
//   for (;;)
//   {
      Move move;

      // prompt
/*      if (numMoves % 2 == 0)
         {
            cout << "White: ";
            cin  >> move.text;

            if (move.text == string("?"))
               displayMenu();
         }
      else
         {
            cout << "Black: ";
            cin  >> move.text;
         }
      if (move.text == string("quit"))
         return 0;
*/
      // parse
            try
            {
               moveParse(move, board);

               // verify
               cout << "\tSource:       ("
                    << (int)move.source.c << ", " << (int)move.source.r
                    << ")\n";
               cout << "\tDestination:  ("
                    << (int)move.dest.c << ", " << (int)move.dest.r
                    << ")\n";
               cout << "\tCapture?      "
                    << (move.capture ? "yes" : "no")
                    << endl;
               cout << "\tKing Castle?  "
                    << (move.castleK ? "yes" : "no")
                    << endl;
               cout << "\tQueen Castle? "
                    << (move.castleQ ? "yes" : "no")
                    << endl;
               cout << "\tPromote?      "
                    << (move.promote ? "yes" : "no")
                    << endl;
               cout << "\tEn Passant?   "
                    << (move.enpassant ? "yes" : "no")
                    << endl;
               cout << "\tPiece:        "
                    << move.piece
                    << endl;
            }
            catch (string s)
            {
               cout << "ERROR: " << s << endl;
            }
//   }
}




void readFile(int numMoves, string moves)
{
   string file;
   
   cout << "Filename: ";
   cin >> file;
   
   ifstream fin(file.c_str());

   if (fin.fail())
   {
      cout << "Unable to open file "
           << file
           << " for input.";
   }
   else
   {
      while (fin >> moves)
         numMoves++;
      fin.close();
   }
}

void writeFile(int numMoves, string moves)
{
   string file;
   
   cout << "To save a game, please specify the filename.\n"
        << "\tTo quit without saving a file, just press <enter>\n";
   cin >> file;
   
   
   ofstream fout(file.c_str());
   
   while (fout << moves)
      numMoves--;
   fout.close();
}





void displayBoard(char board[][8])
{
   for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
         cout << board[i][j] << endl;
}

void displayTest(char board[][8])
{
   for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
         cout << board[i][j] << endl;
}


void displayMenu()
{
   cout << "Options:\n"
        << "?       Display these options\n"
        << "b2b4    Specify a move using the Smith Notation\n"
        << "read    Read a saved game from a file\n"
        << "test    Simple display for test purposes\n"
        << "quit    Leave the game. You will be prompted to save\n";
}





void interact()
{
   char board[8][8] =
   {
         { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' },
         { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
         { NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
           NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE },
         { NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
           NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE },
         { NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
           NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE },
         { NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
           NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE },
         { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
         { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' }
   };

   int turn = 0;

   string moves;

   int numMoves = 0;

   Move move;

   for (;;)
   {
      if (numMoves % 2 == 0)
      {
         cout << "White: ";
         cin >> move.text;

         if (move.text == string("?"))
            displayMenu();
         if (move.text == string("read"))
            readFile(numMoves, moves);
         if (move.text == string("test"))
            displayTest(board);
      }
      else
      {
         cout << "Black: ";
         cin >> move.text;

         if (move.text == string("?"))
            displayMenu();
         if (move.text == string("read"))
            readFile(numMoves, moves);
         if (move.text == string("test"))
            displayTest(board);
         
      }

      cout << move.text << endl;
         moveDriver(board, moves);
   }
   
/*   if (numMoves % 2 == 0)
   {
      cout << "White: ";
      cin >> move.text;
   }
   else
   {
      cout << "Black: ";
      cin >> move.text;
   }

   if (move.text == string("?"))
      displayMenu();
   if (move.text == string("read"))
      readFile(numMoves, moves);
   if (move.text == string("quit"))
      writeFile(numMoves, moves);
   if (move.text == string("test"))
      displayTest(board);
   else
      moveDriver(board, numMoves, moves);

   
   numMoves++;
*/   
   writeFile(numMoves, moves);
}

/*************************
 * Main: Drives chess
 ************************/
int main()
{
   interact();
   return 0;
}
