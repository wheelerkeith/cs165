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
   bool isDead()
   {
     return dead;
   };
   void setDead(bool death)
   {
     dead = death;
   }


   Velocity getVelocity()
   {
     return Move;
   };
protected:
   Velocity Move;                          // Velocity of the Moveable
   bool dead;   
};

#endif // MOVEABLE_H
