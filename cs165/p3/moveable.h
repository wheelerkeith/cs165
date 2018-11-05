/***********************************************************************
 * Header File:
 *    Rifle : A gun
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The class definition and associated constants for a Rifle.  
 ************************************************************************/

#ifndef MOVEABLE_H
#define MOVEABLE_H 
#include "velocity.h"
#include "bird.h"
#include "bullet.h"

/**************************************
 * Moveable
 * Anything that moves on the screen
 * except for the rifle
 **************************************/
class Moveable
{
public:
   virtual void draw() = 0;
   virtual void advance() = 0;
   virtual void getScore() = 0;
   bool getDead()
   {
     return dead;
   };
   Velocity getVelocity()
   {
     return Move;
   };
private:
   Velocity Move;                          // Velocity of the Moveable
protected:
   bool dead;   
};

#endif // RIFLE_H
