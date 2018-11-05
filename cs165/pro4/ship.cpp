#include "ship.h"
#include "point.h"
#include <cmath>      // for M_PI, sin() and cos()
#include "uiDraw.h"

#include <iostream>
using namespace std;

#define SHIPLARGE_CIR_RAD	8
#define SHIPSMALL_CIR_RAD	2

#define MAX_SPEED			12

// *************************************************************************** 
void Ship::draw()
{
	Point tip(cos(deg2rad(rotation)) * SHIPLARGE_CIR_RAD,
			  sin(deg2rad(rotation)) * SHIPLARGE_CIR_RAD);

	Point left(cos(deg2rad(rotation + 140)) * SHIPLARGE_CIR_RAD,
			   sin(deg2rad(rotation + 140)) * SHIPLARGE_CIR_RAD);

	Point right(cos(deg2rad(rotation - 140)) * SHIPLARGE_CIR_RAD,
				sin(deg2rad(rotation - 140)) * SHIPLARGE_CIR_RAD);

	Point back(cos(deg2rad(rotation - 180)) * SHIPSMALL_CIR_RAD,
			   sin(deg2rad(rotation - 180)) * SHIPSMALL_CIR_RAD);

	tip.addX(velocity.getPoint().getX());
	tip.addY(velocity.getPoint().getY());

	this->tip = tip;

	left.addX(velocity.getPoint().getX());
	left.addY(velocity.getPoint().getY());

	right.addX(velocity.getPoint().getX());
	right.addY(velocity.getPoint().getY());

	back.addX(velocity.getPoint().getX());
	back.addY(velocity.getPoint().getY());

	drawLine(tip, left, 1.0, 0.0, 0.0);
	drawLine(left, back, 1.0, 0.0, 0.0);

	drawLine(tip, right, 1.0, 0.0, 0.0);
	drawLine(right, back, 1.0, 0.0, 0.0);
}

// *************************************************************************** 
void Ship::accelerate()
{
	tempdx = cos(deg2rad(rotation)) * 0.7;
	tempdy = sin(deg2rad(rotation)) * 0.7;

	if (fabs(velocity.getDx() + tempdx) < MAX_SPEED)
		velocity.setDx(velocity.getDx() + tempdx);
	
	if (fabs(velocity.getDy() + tempdy) < MAX_SPEED)
		velocity.setDy(velocity.getDy() + tempdy);
}
