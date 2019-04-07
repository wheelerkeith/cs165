#pragma once

// Abstract class for all items in the game with a velocity

#include "velocity.h"

class Moveable
{
public:
   //Constructor: Creates a moveable object
  Moveable(int x, int y, float dx, float dy, bool wrap) : velocity(0, 0, 0, 0)
   {
      velocity.setX((float)x);
      velocity.setY((float)y);
      velocity.setDx(dx);
      velocity.setDy(dy);
      
      velocity.setWrap(wrap);
   };
   
   //Constructor: Creates a moveable object at X and Y location
  Moveable(int x, int y, float dx, float dy, bool wrap, int objectX, int objectY) : velocity(objectX, objectY, 0, 0)
   {
      velocity.setX((float)x);
      velocity.setY((float)y);
      velocity.setDx(dx);
      velocity.setDy(dy);
      
      velocity.setWrap(wrap);
   };
   
   ~Moveable()	{};
   
   int getX()							{ return (int)velocity.getX(); };
   int getY()							{ return (int)velocity.getY(); };
   float getDX()						{ return velocity.getDx(); };
   float getDY()						{ return velocity.getDy(); };
   
   void setPosition(int x, int y)		{ velocity.setX((float)x); velocity.setY((float)y); };
   void setChange(float dx, float dy)	{ velocity.setDx(dx); velocity.setDy(dy); };
   
   virtual void draw() = 0;
   void move()	{ velocity++; };
   Velocity & getVelocity() { return this->velocity; }
   virtual bool isReadyToDie() { return this->velocity.getIsDead(); }
   
protected:
   Velocity velocity;
};
