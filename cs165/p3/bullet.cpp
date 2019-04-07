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

#include "uiDraw.h"
#include "bullet.h"

Bullet::Bullet()
{
   kill();
   
   position.setCheck(true);
}

void Bullet::draw() const
{
   if (isDead())
      return;
   
   drawDot(Point(position.getX(), position.getY());
}


void Bullet::advance()
{
   if (isDead())
      return;
      
   position.advance();
   
   if (position.isDead())
      kill();
}

void Bullet::kill()
{
   position.setDead(true);
}


void Bullet::fire(Rifle & rifle)
{
   // finds rifles position
   position.setX(position.getXMax() - 1);
   position.setY(position.getYmin() + 1);
   
   // fires from the rifle
   position.setDx(-cos(deg2rad((float)rifle.getAngle())) * SPEED);
   position.setDy( sin(deg2rad((float)rifle.getAngle())) * SPEED);
   position.setDead(true);  // not loaded
}