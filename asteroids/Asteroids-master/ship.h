#pragma once
#include "moveable.h"

#define ROTATION		6

class Ship : public Moveable
{
public:
	Ship(int x, int y, double dx, double dy) : Moveable(x, y, dx, dy, true), rotation(0)    {};
	~Ship()					{};

	void draw();

	int getRotation()	{ return rotation; };

	void rotateLeft()	{ rotation += ROTATION; };
	void rotateRight()	{ rotation -= ROTATION; };

	void rocketBurst();
	Point getTip() { return this->tip; }

private:
	int rotation;
	Point tip;
};