#pragma once
#include "moveable.h"

#define ROTATION		6

class Ship : public Moveable
{
public:
   Ship(int x, int y, float dx, float dy) : Moveable(x, y, dx, dy, true), rotation(0)    { velocity.setIsDead(false); };
	~Ship()					{};

	void draw();

	int getRotation()	{ return rotation; };

	void rotateLeft()	{ rotation += ROTATION; };
	void rotateRight()	{ rotation -= ROTATION; };

   void accelerate();
	Point getTip() { return this->tip; }

private:
	int rotation;
   float tempdx;
   float tempdy;
	Point tip;
};