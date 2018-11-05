/***********************************************************************
 * Source File:
 *    Skeet ++ - main file for this game
 * Author:
 *    Br. Comeau
 * Summary:
 *    This project will impliment the Skeet game outlined in the cs165
 *    textbook.
 ************************************************************************/

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "rifle.h"
#include "moveable.h"

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   // create the game
   Game() : gameOver(false) {}
   
   // handle user input
   void input(const Interface & ui);

   // advance the game
   void advance();
         
   // draw stuff
   void draw(const Interface & ui) const;
   
   int getNumBullets()
   {
     return numBullets;
   };
   
   void setNumBullets(int add)
   {
     numBullets += add;
   };
   
   bool getHit() { return hit; };
   void setHit(bool t) { hit = t; }
   
private:
   
   bool gameOver;
   Rifle rifle;
   int numBullets;
   Bird *bird;
   bool hit;
   int miss;
   int score;
   
   // TODO - REQUIREMENT for this project!!!!
   //      - you must use/have a pointer to a bird object
   //      - Ie., Bird *bird;

   // TODO: add any objects or variables that are required
};

/***************************************
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   // TODO: advance anything that moves
   // TODO: decide if anything died, the game is over, etc...
}

/***************************************
 * GAME :: input
 * accept input from the user
 ***************************************/
void Game :: input(const Interface & ui)
{
   // TODO: handle user input

   // Note that you can discover keys that were pressed by checking
   // methods such as ui.isUp(), ui.isLeft(), etc.
   // see Pong for an example

   // Move the the rifle
   rifle.move(ui.isRight(), ui.isLeft());
   // If space is pressed, create a bullet
   if (ui.isSpace() && getNumBullets() <= 5)
   {
     new Bullet();
     setNumBullets(1);
   }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui) const
{
	// display the rifle
   	rifle.draw();

    // TODO: draw anything you need to display in the game

}

#define X_SIZE       400

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   Game *pGame = (Game *)p;

   pGame->advance();
   pGame->input(*pUI);
   pGame->draw(*pUI);
}

// set the bounds of the drawing rectangle
float Point::xMin = -(X_SIZE / 2.0);
float Point::xMax =  (X_SIZE / 2.0);
float Point::yMin = -200.0;
float Point::yMax =  200.0;

/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Skeet");
   Game game;
   ui.run(callBack, &game);
   
   return 0;
}
