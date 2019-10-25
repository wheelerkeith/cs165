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
#include <vector>
#include <list>

using namespace std;

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
   void draw(const Interface & ui);
   
private:
   
   // Sample code on how to use a vector
   // delete it if you don't need it
   vector<Point> points;

   bool gameOver;
   int rotate;
   bool up;
   bool down;
   bool left;
   bool right;
   
   // TODO: Create ship, bullets and rocks
   // TODO: add any objects or variables that are required

   void detectHits();
   void removeDeadObjects();

};

/***************************************
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   // TODO: advance anything that moves

   // Decide if anything died, the game is over, etc...
   detectHits();

   // TODO - is the game over? or did the user shot all of the rocks?
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

/*  // Vector example
  if (ui.isUp())
  {
    // create 10 random points and add them to the vector
    for (int i = 0; i < 10; i++)
    {
      points.push_back(Point(random(Point::xMin, Point::xMax), random(Point::xMin, Point::xMax)));
    }
  }

  if (ui.isDown() && (points.size() > 0))
  {
    // go through all points and kill some of them
    // Notice that the For loop doesn't increment "it" in the normal place 
    for (vector<Point>::iterator it = points.begin(); it != points.end();)
    {
      // delete some random points
      if (random(1, 10) == 5)
      {
	// When you delete a point, don't move the iterator
	it = points.erase(it);
      }
      else
      {
        // Move to the next point in the vector
	++it;
      }
    }
  }*/
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
    // TODO: draw anything you need to display in the game

 /* // Vector example
  Point pt(-50, 0);
  drawText(pt, "Press UP and DOWN");

  string str = "Point count = " + convertIntToString(points.size());
  pt.addY(-20);
  drawText(pt, str.c_str());

  // draw all of the points
  for (vector<Point>::iterator it = points.begin(); it != points.end(); ++it)
  {
    drawDot(*it);
  }*/
}

/*********************************************
 * GAME :: detectHits
 * Detect any rocks hitting bullets and ship and make them "dead"
 * Note: decide if the game is over here
 *********************************************/
void Game::detectHits()
{
  // did any bullets hit a rock?

  // did the ship hit a rock?

  // remove the dead
  removeDeadObjects();
}

/*********************************************
 * GAME :: removeDeadObjects
 * remove any "dead" rocks, bullets, etc...
 *********************************************/
void Game::removeDeadObjects()
{
  // TODO: Remove any dead objects (ie., rocks, bullets, etc...)

  // TODO: Create any new rocks (Large rock -> mid rock and mid -> small)
}

#define X_SIZE       600

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
float Point::yMin = -300.0;
float Point::yMax =  300.0;

/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Hunter");
   Game game;
   ui.run(callBack, &game);
   
   return 0;
}
