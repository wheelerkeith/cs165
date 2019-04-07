#pragma once
#include "moveable.h"
class Asteroid : public Moveable
{
public:
   Asteroid(int x, int y, float dx, float dy, int id) : Moveable(x, y, dx, dy, true)
   {
      vel.setIsDead(false);
      num = id;
   }
   void draw();
   void move();
   int getRadius() { return 1; }
   bool isReadyToDie() { return vel.getIsDead();  }

public:
   int num;
   int radius;
   Velocity vel;
};
/*
class Asteroid : public Moveable
{
  public:
  Asteroid(int x, int y, float dx, float dy, int id) : Moveable(x, y, dx, dy, true),
      radius(y), id(id) 
  {
     this->velocity.setDx(dx);
     this->velocity.setDy(dy);
  };
   ~Asteroid()	{ };

   
   void draw();
   void live();
   int getRadius() { return this->radius; }
  private:
   int radius;
   int id;
};*/
