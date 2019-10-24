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
   Game() : dead(false), landed(false), fuel(FUEL), bDown(false), bLeft(false), bRight(false)
   {
       player1.setY(157);
       player1.setX(175);

//      lander.setDx(175);
//      lander.setDy(175);
   }
   
   // handle user input
   void input(const Interface & ui);
   
   // advance the game
   void advance();
         
   // draw stuff
   void draw();
   
private:
   bool justLanded();
   
   int  fuel;
   bool dead;
   bool landed;
   Lander player1;
   Ground ground;
   bool bDown;
   bool bLeft;
   bool bRight;

   // TODO: add any objects or variables that are required
};

/******************************************
 * GAME :: LANDED
 * Did we land successfully?
 ******************************************/
bool Game :: justLanded()
{
   Point pos  = player1.getPoint();
   Point posp = ground.getPlatformPosition();
   int width  = ground.getPlatformWidth();
   // TODO: indicate if the lander has landed
   if (pos.getX() < posp.getX() + width / 2 &&
       pos.getX() > posp.getX() - width / 2 &&
       pos.getY() < posp.getY() + 5 &&
       pos.getY() > posp.getY() - 5 &&
       player1.getMag() < MIN_SPEED)
   {
      landed = true;
      return true;
   }
   if (pos.getX() < posp.getX() + width / 2 &&
       pos.getX() > posp.getX() - width / 2 &&
       pos.getY() < posp.getY() + 5 &&
       pos.getY() > posp.getY() - 5 &&
       player1.getMag() > MIN_SPEED)
   {
      landed = true;
      dead = true;
      return false;
   }
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   Point pos1(0, 150);
   Point pos = player1.getPoint();
   // TODO: move lander and check for crashed
   if (dead == false && landed == false)
      player1.advance(bDown, bLeft, bRight);
   if (ground.crashed(pos))
   {
     drawText(pos1, "[You Crashed!]");
     dead = true;
   }
   if (justLanded())
      drawText(pos1, "[You Landed!]");
   if (landed == true && dead == true)
      drawText(pos1, "[You Crashed]");
}

/***************************************
 * GAME :: input
 * accept input from the user
 ***************************************/
void Game :: input(const Interface & ui)
{
   // TODO: handle user input
      bDown  = ui.isDown();
      bLeft  = ui.isLeft();
      bRight = ui.isRight();
 

   // Note that you can discover keys that were pressed by checking
   // methods such as ui.isUp(), ui.isLeft(), etc.
   // see Pong for an example
      

}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw()
{
   Point pos;
 
   // TODO: draw the lander or a status message
   player1.draw(bDown, bLeft, bRight);

   // TODO: draw the fuel
   pos.setX(-175);
   pos.setY(175);
   
   drawNumber(pos, player1.getFuel());
   
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
   
   pGame->advance();
   
   pGame->input(*pUI);
   
   pGame->draw();
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
