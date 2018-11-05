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

	tip.addX(path.getPoint().getX());
	tip.addY(path.getPoint().getY());

	this->tip = tip;

	left.addX(path.getPoint().getX());
	left.addY(path.getPoint().getY());

	right.addX(path.getPoint().getX());
	right.addY(path.getPoint().getY());

	back.addX(path.getPoint().getX());
	back.addY(path.getPoint().getY());

	drawLine(tip, left, 1.0, 0.0, 0.0);
	drawLine(left, back, 1.0, 0.0, 0.0);

	drawLine(tip, right, 1.0, 0.0, 0.0);
	drawLine(right, back, 1.0, 0.0, 0.0);
}

// *************************************************************************** 
void Ship::rocketBurst()
{
	double dx = cos(deg2rad(rotation)) * 0.7;
	double dy = sin(deg2rad(rotation)) * 0.7;

	if (fabs(path.getDx() + dx) < MAX_SPEED)
		path.setDx(path.getDx() + dx);
	
	if (fabs(path.getDy() + dy) < MAX_SPEED)
		path.setDy(path.getDy() + dy);
}
