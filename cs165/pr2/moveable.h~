#pragma once

// Abstract class for all items in the game that can move (ie., has a path)

#include "path.h"

class Moveable
{
public:
	//Constructor: Creates a moveable object in the center of the screen
	Moveable(int x, int y, double dx, double dy, bool wrap) : path(0, 0)
	{
		path.setX((double)x);
		path.setY((double)y);
		path.setDx(dx);
		path.setDy(dy);

		path.setWrap(wrap);
	};

	//Constructor: Creates a moveable object at the objectX and objectY location
	Moveable(int x, int y, double dx, double dy, bool wrap, int objectX, int objectY) : path(objectX, objectY)
	{
		path.setX((double)x);
		path.setY((double)y);
		path.setDx(dx);
		path.setDy(dy);

		path.setWrap(wrap);
	};

	~Moveable()	{};

	int getX()							{ return (int)path.getX(); };
	int getY()							{ return (int)path.getY(); };
	double getDX()						{ return path.getDx(); };
	double getDY()						{ return path.getDy(); };

	void setPosition(int x, int y)		{ path.setX((double)x); path.setY((double)y); };
	void setChange(double dx, double dy)	{ path.setDx(dx); path.setDy(dy); };

	virtual void draw() = 0;
	void move()	{ path++; };
	Path & getPath() { return this->path; }
	virtual bool isReadyToDie() { return this->path.isDead(); }

protected:
	Path path;
};

