/***********************************************************************
 * Program:
 *    Project 2, Skeet
 * Author:
 *    Ryan Allred
 *    Marc Schwartz
 * Summary:
 *    // Description
 ***********************************************************************/

#include <cmath>
#include "bullet.h"
#include "uiDraw.h"

#define SPEED 10
#define deg2rad(value) ((M_PI / 180) * (value))

/*******************************************************
 * CONSTRUCTOR
 *******************************************************/
Bullet::Bullet()
{
   //Initialized as dead (we bring it to life later)
   kill();

   //Do bounds checking
   position.setCheck(true);
}

/*********************************************************
 * FIRE
 *  Fires a bullet from the rifle (if one is available)
 *    INPUT:  rifle - state of the rifle (especially angle)
 *    OUTPUT: -
 **********************************************************/
void Bullet::fire(Rifle & rifle)
{
   //Puts bullet at rifle
   position.setX(position.getXMax() - 1);
   position.setY(position.getYMin() + 1);

   //Fires at the angle of the rifle
   position.setDx(-cos(deg2rad((float)rifle.getAngle())) * SPEED);
   position.setDy( sin(deg2rad((float)rifle.getAngle())) * SPEED);
   position.setDead(true);   //aka "not loaded"

   return;
}

/************************************************************
 * UPDATE
 *  Moves the bullet forward
 *    INPUT:  -
 *    OUTPUT: -
 ************************************************************/
void Bullet::update()
{
   //Can't do anything once it's fired
   if (isDead())
      return;

   //Move it along
   position.advance();

   //Bounds checking
   if (position.isDead())
      kill();
}

/*************************************************************
 * DRAW
 *  Actually prints the bullet to the screen at its position
 *    INPUT:  -
 *    OUTPUT: -
 *************************************************************/
void Bullet::draw()
{
   //We don't draw an dead bullet
   if (isDead())
      return;

   //New bullet!
   drawDot(Point(position.getX(),position.getY()));

   return;
}

/**************************************************************
 * KILL
 *  Kills the bullet when it goes out of bounds or hits its target
 *    INPUT:  -
 *    OUTPUT: -
 **************************************************************/
void Bullet::kill()
{
   //Like a candle flickering out...
   position.setDead(true);
}