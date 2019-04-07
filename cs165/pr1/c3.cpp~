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
#define WHITE_WHITE             "\E[31;47m"
#define WHITE_BLACK             "\E[30;47m"
#define BLACK_WHITE             "\E[37;41m"
#define BLACK_BLACK             "\E[30;41m"
#define END_COLOUR_CODE         "\E[0m"


struct Coord
{
   char r;   // row, from 0..7
   char c;   // col, from 0..7
};


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

void updateBoard(char board[][8], Move move);


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

void moveDriver(char board[][8], string & moves, Move move)
{

   // parse
   try
   {
      moveParse(move, board);
      cout << move.text;

   }
   catch (string s)
   {
      cout << "ERROR: " << s << endl;
      return;
   }

   moves.append(move.text);

   updateBoard(board, move);

}





void getInput(int turn, Move & move)
{
   
   if (turn % 2 == 0)
   {
      cout << "(White): ";
      cin  >> move.text;
   }

   else
   {
      cout << "(Black): ";
      cin  >> move.text;
   }

}

void readFile(int numMoves, string moves)
{
   char file[256];

   cout << "Filename: ";
   cin.ignore();
   cin.getline(file, 256);

   // ifstream fin(file.c_str());
   ifstream fin(file);
   
   if (fin.fail())
   {
      cout << "Unable to open file "
           << file
           << " for input.";
   }
   else
   {
      while (fin >> moves)
      {
         numMoves++;
      }
      fin.close();
   }
}


void writeFile(int numMoves, string moves)
{
   char file[256];

   cout << "To save a game, please specify the filename.\n"
        << "\tTo quit without saving a file, just press <enter>\n";
   cin.ignore();
   cin.getline(file, 256);

   ofstream fout;
   fout.open(file);

   if (fout.fail())
      return;
   
   fout << moves;

   fout.close();

   return;
}


void displaySquare(bool isWhitePlayer, bool isWhiteSquare, char symbol)
{
   if (isWhiteSquare)
      cout << (isWhitePlayer ? WHITE_WHITE : WHITE_BLACK);
   else
      cout << (isWhitePlayer ? BLACK_WHITE : BLACK_BLACK);

   cout << " " << symbol << " ";
   cout << END_COLOUR_CODE;
}

bool isWhiteSquare(char board[][8], int i, int j)
{
   if ((i + j) % 2 == 0)
      return true;
   else
      return false;

}

void displayBoard(char board[][8])
{
   cout << "\E[H\E[2J";
   
   cout << "   a  b  c  d  e  f  g  h " << endl;
   
   for (int i = 7; i >= 0; i--)
   {
      cout << i + 1 << ' ';
      for (int j = 7; j >= 0; j--)
      {
         switch(board[i][j])
         {
            case 'R':
               displaySquare(false, isWhiteSquare(board, i, j), 'R');
               break;
            case 'N':
               displaySquare(false, isWhiteSquare(board, i, j), 'N');
               break;
            case 'B':
               displaySquare(false, isWhiteSquare(board, i, j), 'B');
               break;
            case 'Q':
               displaySquare(false, isWhiteSquare(board, i, j), 'Q');
               break;
            case 'K':
               displaySquare(false, isWhiteSquare(board, i, j), 'K');
               break;
            case 'P':
               displaySquare(false, isWhiteSquare(board, i, j), 'p');
               break;
            case 'r':
               displaySquare(true, isWhiteSquare(board, i, j), 'R');
               break;
            case 'n':
               displaySquare(true, isWhiteSquare(board, i, j), 'N');
               break;
            case 'b':
               displaySquare(true, isWhiteSquare(board, i, j), 'B');
               break;
            case 'q':
               displaySquare(true, isWhiteSquare(board, i, j), 'Q');
               break;
            case 'k':
               displaySquare(true, isWhiteSquare(board, i, j), 'K');
               break;
            case 'p':
               displaySquare(true, isWhiteSquare(board, i, j), 'p');
               break;
            default:
               displaySquare(false, isWhiteSquare(board, i, j), ' ');
               break;
         }
      }
      cout << endl;
   }
}

void displayTest(char board[][8])
{
   cout << "  abcdefgh\n";
   for (int i = 7; i >= 0; i--)
   {
      cout << i + 1 << ' ';
      for (int j = 7; j >= 0; j--)
      {
         if (board[i][j] == '*')
            cout << " ";
         else
            cout << board[i][j];
      }
      cout << endl;
   }
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


void updateBoard(char board[][8], Move move)
{
   switch(move.text[0])
   {
      case 'a':
         move.source.c = 7;
         break;
      case 'b':
         move.source.c = 6;
         break;
      case 'c':
         move.source.c = 5;
         break;
      case 'd':
         move.source.c = 4;
         break;
      case 'e':
         move.source.c = 3;
         break;
      case 'f':
         move.source.c = 2;
         break;
      case 'g':
         move.source.c = 1;
         break;
      case 'h':
         move.source.c = 0;
         break;
         
   }


   switch(move.text[1])
   {
      case '1':
         move.source.r = 0;
         break;
      case '2':
         move.source.r = 1;
         break;
      case '3':
         move.source.r = 2;
         break;
      case '4':
         move.source.r = 3;
         break;
      case '5':
         move.source.r = 4;
         break;
      case '6':
         move.source.r = 5;
         break;
      case '7':
         move.source.r = 6;
         break;
      case '8':
         move.source.r = 7;
   }


      switch(move.text[2])
   {
      case 'a':
         move.dest.c = 7;
         break;
      case 'b':
         move.dest.c = 6;
         break;
      case 'c':
         move.dest.c = 5;
         break;
      case 'd':
         move.dest.c = 4;
         break;
      case 'e':
         move.dest.c = 3;
         break;
      case 'f':
         move.dest.c = 2;
         break;
      case 'g':
         move.dest.c = 1;
         break;
      case 'h':
         move.dest.c = 0;
   }


      switch(move.text[3])
   {
      case '1':
         move.dest.r = 0;
         break;
      case '2':
         move.dest.r = 1;
         break;
      case '3':
         move.dest.r = 2;
         break;
      case '4':
         move.dest.r = 3;
         break;
      case '5':
         move.dest.r = 4;
         break;
      case '6':
         move.dest.r = 5;
         break;
      case '7':
         move.dest.r = 6;
         break;
      case '8':
         move.dest.r = 7;
   }

      cout << move.source.c << move.source.r << move.dest.c << move.dest.r;

      char change;
      board[move.dest.r][move.dest.c] = board[move.source.r][move.source.c];
      board[move.source.r][move.source.c] = '*';
      

//      board[move.dest.c][move.dest.r] = change;
      

      
//      board[move.source.c][move.source.r] = board[move.dest.c][move.dest.r];
//      board[move.text[2]][move.text[3]] = board[move.text[0]][move.text[1]];
//      board[move.source.c][move.source.r] == ' ';

}

void interact()
{
   char board[8][8] =
   {
         { 'r', 'n', 'b', 'k', 'q', 'b', 'n', 'r' },
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
         { 'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R' }
   };

   Move move;
   
   string file;

   int turn = 0;

   string moves;

   bool isTest = false;

   displayBoard(board);
   
   for (;;)
   {
      while (move.text != string("quit"))
         {
            getInput(turn, move);

            if (move.text == string("?"))
            {
               displayMenu();
               getInput(turn, move);
            }
            else if (move.text == string("read"))
            {
               readFile(turn, moves);
               if (isTest = true)
                  displayTest(board);
               else
                  displayBoard(board);
               getInput(turn, move);
            }
            else if (move.text == string("test"))
            {
               isTest = true;
               
               displayTest(board);
               getInput(turn, move);
            }
            else if (move.text == string("quit"))
            {
               writeFile(turn, moves);
               return;
            }

            moveDriver(board, moves, move);


//            for (int i = 0; i < move.dest.r; i++)
//            {
//               for (int j = 0; j < move.dest.c; j++)
//               {
//                  board[move.dest.r][move.dest.c] >> board[move.source.r][move.source.c];
//               }
//            }


            if (isTest == true)
               displayTest(board);
            else
               displayBoard(board);
            turn++;
         }
   }
}

/*************************
 * Main: Drives chess
 ************************/
int main()
{
   interact();
   return 0;
}
