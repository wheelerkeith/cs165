/***********************************************************************
 * Header File:
 *    Rifle : A gun
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The class definition and associated constants for a Rifle.  
 ************************************************************************/

#ifndef RIFLE_H
#define RIFLE_H

// length of the rifle
#define LENGTH_RIFLE 20 

/**************************************
 * RIFLE
 * Where the rifle is pointing and stuff
 **************************************/
class Rifle
{
public:
   Rifle() : angle(45) {}              // rifle pointed neutrally by default
   void move(int up, int down);        // move the rifle up or down
   void draw()     const;              // draw the rifle at the current angle
   int  getAngle() const { return angle; }
private:
   int angle;                          // angles between 0 .. 90
};

#endif // RIFLE_H
