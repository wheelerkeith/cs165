/***********************************************************************
 * Program:
 *    Project 2, Skeet
 * Author:
 *    Ryan Allred
 *    Marc Schwartz
 * Summary:
 *    // Description
 ***********************************************************************/

#ifndef BULLET_H
#define BULLET_h

#include "vector.h"
#include "rifle.h"

class Bullet
{
  private:
   Vector position;
   bool alive;
   
  public:
   Bullet();
   const bool isDead() const { return position.isDead(); };  //Extend getter
   void fire(Rifle & rifle);
   void update();
   void draw();
   void kill();
};

#endif