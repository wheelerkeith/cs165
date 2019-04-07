#pragma once
#include "moveable.h"

class Bullet : public Moveable
{
public:
  Bullet(int x, int y, float dx, float dy, int rotation) : Moveable(x, y, dx, dy, true), movesCounter(0), radius(2)
   {
      float rotx = cos(deg2rad(rotation)) * 4;
      float roty = sin(deg2rad(rotation)) * 4;
      this->velocity.setDx(rotx);
      this->velocity.setDy(roty);
   };
   ~Bullet() {};
   
   void draw();
   
   void moveBullet();
   bool isReadyToDie() { return this->movesCounter > (Point::xMax/2) - 10; }
   int getRadius() { return this->radius; }
   int getMovesCounter() { return this->movesCounter; }
private:
   int movesCounter;
   int radius;
};

