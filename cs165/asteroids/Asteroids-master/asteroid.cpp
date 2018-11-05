#include "Asteroid.h"
#include "point.h"
#include <cmath>      // for M_PI, sin() and cos()
#include "uiDraw.h"

#include <iostream>
using namespace std;

// *************************************************************************** 
void Asteroid::draw()
{
	drawCircle(path.getPoint(), this->radius, 0.0, 1.0, 0.0);
}
