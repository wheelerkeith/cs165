#include "Bullet.h"
#include "point.h"
#include <cmath>      // for M_PI, sin() and cos()
#include "uiDraw.h"

#include <iostream>
using namespace std;

// *************************************************************************** 
void Bullet::draw()
{
	drawCircle(path.getPoint(), this->getRadius() );
}

void Bullet::moveBullet()
{
	this->move();
	movesCounter++;
}