/***********************************************************************
 * Program:
 *    Project 2, Skeet
 * Author:
 *    Ryan Allred
 *    Marc Schwartz
 * Summary:
 *    // Description
 ***********************************************************************/

#include <iostream>
#include "velocity.h"
#include "uiInteract.h"  // interface with OpenGL
#include "uiDraw.h"      // all the draw primitives exist here
#include "point.h"       // 
#include "bird.h"        // bird to be shot (heheheh)
#include "rifle.h"       // there are many like it...
#include "bullet.h"      // five shots, one kill

#define NUM_BULLETS 5          //Up to five bullets onscreen

/**************************************************
 * SKEET Class
 *  Used to play the game of skeet. Involves a gun, a bird,
 *   and some bullets.
 **************************************************/
class Skeet
{
  private:
   Rifle rifle;                  //Gun
   Bird bird;                    //Pigeon
   Bullet bullets[NUM_BULLETS];  //An array of bullet objects
   unsigned int hit;             //Number of hits    (can't be negative)
   unsigned int miss;            //Number of misses  (can't be negative)
   
  public:
   Skeet();                      //Constructor
   ~Skeet();                     //Destructor
   void setup();
   void update(const Interface *pUI);
   void draw();
   void setHit(unsigned int value) {hit = value;}
   void setMiss(unsigned int value) {miss = value;}
};

/****************************************************
 * CONSTRUCTOR
 *  At the beginning of the game, the score is 0-0
 ****************************************************/
Skeet::Skeet()
{
   hit = 0;
   miss = 0;
}

/****************************************************
 * DESTRUCTOR
 *  Deletes memory
 ****************************************************/
Skeet::~Skeet()
{
}

/****************************************************
 * SETUP
 *  (Possibly redundant with constructor?)
 ****************************************************/
void Skeet::setup()
{
   bird.respawn();
   rifle.move(0,0);
 //  hit = 0;
 //  miss = 0;

   return;
}

/******************************************************
 * UPDATE
 *  Moves everything to the next frame
 *   INPUT:  *pUI - a pointer to the UI object
 *   OUTPUT: -
 *******************************************************/
void Skeet::update(const Interface *pUI)
{
   //Moves bird along
   bird.update();
   
   //If it moves out-of-bounds, make another
   if (bird.isOutside())
   {
      bird.respawn();
      miss++;
   }

   //Moves gun
   rifle.update();

   //Moves bullets
   for(int i = 0; i < NUM_BULLETS; ++i)
   {
      bullets[i].update();
   }

   //Commands firing
   if (pUI->isSpace())
      for(int i = 0; i < NUM_BULLETS; ++i)
         if (bullets[i].isDead())
         {
            bullets[i].fire(rifle);
            i = NUM_BULLETS;
         }

   //Moves rifle left or right (?)
   if (pUI->isLeft() || pUI->isRight())
      rifle.move(pUI->isLeft(),pUI->isRight());

   return;
}

void Skeet::draw()
{
   //Draw bird
   bird.draw();

   //Draw rifle
   rifle.draw();

   //Draw each bullet (or each one that should be onscreen)
   for(int i = 0; i < NUM_BULLETS; ++i)
   {
      if (!bullets[i].isDead())  //Only draw if it isn't dead
         bullets[i].draw();
   }

   //Position for the "hit" score
   Point pt1 = Point(pt1.getXMin()+10,pt1.getYMax()-10);
   drawNumber(pt1,hit);   //...and draw it

   //Position for the "miss" score
   Point pt2 = Point(pt2.getXMax()-100,pt2.getYMax()-10);
   drawNumber(pt2,miss);  //...and draw it
}

/*********************************************
 * CALLBACK
 * The main interaction loop of the engine.
 * This gets called from OpenGL.  It give us our
 * interface pointer (where we get our events from)
 * as well as a void pointer which we know is our
 * game class.
 *********************************************/
void callBack(const Interface *pUI, void *p)
{
   Skeet *game = (Skeet *)p;
   game->update(pUI);
   game->draw();

   return;
}

/*********************************
 * MAIN
 * initialize the drawing window, initialize
 * the game,and run it!
 *********************************/
int main(int argc, char **argv)
{
   //Initialize the game
   Interface ui(argc, argv, "Skeet!");
   Skeet game;

   //Start the display (run the game!)
   ui.run(callBack, (void *)&game);
   
   return 0;
}
