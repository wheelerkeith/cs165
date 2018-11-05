/***********************************************************************
 * Program:
 *    Project 2, Skeet
 * Author:
 *    Ryan Allred
 *    Marc Schwartz
 * Summary:
 *    // Description
 ***********************************************************************/

#include "point.h"
#include "vector.h"

#define BIRD_SIZE 10

class Bird
{
  private:
   Vector position;
   
  public:
   Bird();           //Constructor
   void update();    
   void draw();
   void respawn();
   bool isOutside();
};