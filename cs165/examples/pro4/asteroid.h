#pragma once
#include "moveable.h"

class Asteroid : public Moveable
{
  public:
  Asteroid(int x, int y, float dx, float dy, int id) : Moveable(x, y, dx, dy, false),
      radius(y), id(id) {};
   ~Asteroid()	{ };
   
   void draw();
   int getRadius() { return this->radius; }
  private:
   int radius;
   int id;
};
