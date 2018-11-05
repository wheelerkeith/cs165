/***********************************************************************
 * Program:
 *    Project 2, Skeet
 * Author:
 *    Ryan Allred
 *    Marc Schwartz
 * Summary:
 *    // Description
 ***********************************************************************/

#include "bird.h"
#include "uiDraw.h"

/***********************************************************************
 * CONSTRUCTOR
 *  Creates bird object; begins with bird at starting position
 ***********************************************************************/
Bird::Bird()
{
   //Reset position
   position.setX(position.getXMin());                               //Left side
   position.setY(random(position.getXMin(), position.getXMax()));   //Random

   //Set dx, dy
   position.setDx(random(3.0, 6.0));
   if (position.getY() > 0)         //Upper half of the screen
      position.setDy(random(-4.0, 0.0)); 
   else                             //Lower half of the screen
      position.setDy(random(0.0, 4.0));
}

/***********************************************************************
 * UPDATE
 *  Moves the bird by frame
 *    INPUT:  -
 *    OUTPUT: -
 ***********************************************************************/
void Bird::update()
{
   if (position.getDx() == 0) //Default is zero; make a new bird!
      respawn();

//   position.setDy(position.getDy() + random(-1.0, 1.0));  //Gravity
   
   //Keep moving forward
   position.advance();

   return;
}

/*************************************************************************
 * DRAW
 *  Prints the bird to the screen at its position
 *    INPUT:  -
 *    OUTPUT: -
 *************************************************************************/
void Bird::draw()
{
   //Initialization
   int x = position.getX();
   int y = position.getY();

   //The bird is a circle...
   drawCircle(Point(x, y), BIRD_SIZE, BIRD_SIZE, 0); //...with some other stuff
   drawLine(Point(x + BIRD_SIZE, y), Point( x + BIRD_SIZE * 2, y-4));  
   drawLine(Point(x + BIRD_SIZE/2, y - BIRD_SIZE/2 - 2),
            Point( x + BIRD_SIZE * 2, y-4));
   drawDot(Point(x - 2, y + 2));   //Left  eye
   drawDot(Point(x + 2, y + 2));   //Right eye
   drawLine(Point(x-4, y - BIRD_SIZE+1), Point(x-6, y - BIRD_SIZE * 1.5));//lleg
   drawLine(Point(x+4, y - BIRD_SIZE+1), Point(x+6, y - BIRD_SIZE * 1.5));//rleg

   return;
}

/***************************************************************************
 * RESPAWN
 *  Makes a new bird at the left side of the screen after the old one is gone
 *    INPUT:  -
 *    OUTPUT: -
 ****************************************************************************/
void Bird::respawn()
{
   //Reset position
   position.setX(position.getXMin());                               //Left side
   position.setY(random(position.getXMin(), position.getXMax()));   //Random

   //Set dx, dy
   position.setDx(random(3.0, 6.0));
   if (position.getY() > 0)         //Upper half of the screen
      position.setDy(random(-4.0, 0.0)); 
   else                             //Lower half of the screen
      position.setDy(random(0.0, 4.0));

   return;
}

/***************************************************************************
 * ISOUTSIDE
 *  Finds if the bird is out of bounds
 *    INPUT:  -
 *    OUTPUT: returns true of out-of-bounds
 ***************************************************************************/
bool Bird::isOutside()
{
   int padding = random(50, 100); //For neatness; doesn't disappear instantly

   //Out of bounds?
   return (
         (position.getX() > position.getXMax() + padding) ||
         (position.getY() > position.getYMax() + padding) ||
         (position.getY() < position.getYMin() - padding)
   );
}
