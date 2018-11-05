/****************************************
 * The game of moonlander
 ****************************************/

#include "uiDraw.h"
#include "uiInteract.h"
#include "ground.h"
#include "lander.h"

#define FUEL        500    // initial fuel for the game
#define MIN_SPEED   3.0    // minimal landing speed
#define FALL_HEIGHT 4.0    // greatest height we can fall from

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   // create the game
   Game() : dead(false), landed(false), fuel(FUEL), bUp(false), bLeft(false), bRight(false) {}
   
   // handle user input
   void input(const Interface & ui);
   
   // advance the game
   void advance(const Interface & ui);
         
   // draw stuff
   void draw(const Interface & ui) const;
   
private:
   bool justLanded() const;
   
   int  fuel;
   bool dead;
   bool landed;
   Lander player1;
   Ground ground;
   Point partake;
   Velocity vel;
   bool bUp;
   bool bLeft;
   bool bRight;

   // TODO: add any objects or variables that are required
};

/******************************************
 * GAME :: LANDED
 * Did we land successfully?
 ******************************************/
bool Game :: justLanded() const
{
   // TODO: indicate if the lander has landed
      return false;
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance(const Interface & ui)
{
   // TODO: move lander and check for crashed
   player1.advance(bUp, bLeft, bRight);
   draw(ui);
}

/***************************************
 * GAME :: input
 * accept input from the user
 ***************************************/
void Game :: input(const Interface & ui)
{
   // TODO: handle user input
   if (ui.isUp())
      bUp = true;
   else
      bUp = false;
   if (ui.isLeft())
      bLeft = true;
   else
      bLeft = false;
   if (ui.isRight())
      bRight = true;
   else
      bRight = false;
   

   // Note that you can discover keys that were pressed by checking
   // methods such as ui.isUp(), ui.isLeft(), etc.
   // see Pong for an example
      

}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface &ui) const
{
   Point pos;
 
   // TODO: draw the lander or a status message
   player1.draw(bUp, bLeft, bRight);

   // TODO: draw the fuel
   pos.setX(-175);
   pos.setY(175);
   
   drawNumber(pos, fuel);
   
   // draw ground
   ground.draw();
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
   
   pGame->advance(*pUI);
   
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
   Interface ui(argc, argv, "Moon Lander");
   Game game;
   ui.run(callBack, &game);
   
   return 0;
}
