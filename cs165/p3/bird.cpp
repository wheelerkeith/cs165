/***********************************************************************
 * Source File:
 *    Rifle : A gun
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The implementation file for the Rifle class, one component
 *    of the Skeet game
 ************************************************************************/

#include <cassert>

#include "point.h"
#include "uiDraw.h"
#include "bird.h"


Bird::Bird()
{
   position.setX(position.getXMin());
   position.setY(random(position.getXMin(), position.getXMax()));
   
   position.setDx(random(3.0, 6.0));
   if (position.getY() > 0)         
      position.setDy(random(-4.0, 0.0)); 
   else                             
      position.setDy(random(0.0, 4.0));
}

void Bird::advance()
{
   if (position.getDx() == 0)
      respawn();
   
   position.advance();
}

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

void Normal::draw() const
{
   int x = position.getX();
   int y = position.getY();
   
   drawCircle(Point(x, y), BIRD_SIZE, BIRD_SIZE, 0);
}

void Tough::draw() const
{
   int x = position.getX();
   int y = position.getY();
   
   drawCircle(Point(x, y), BIRD_SIZE, BIRD_SIZE, 0);
   drawNumber(Point(x, y), 3);
}

void Safe::draw() const
{
   int x = position.getX();
   int y = position.getY();
   
   drawStar(Point(x, y), BIRD_SIZE, 0);
}