/***********************************************************************
 * Header File:
 *    Bullet: comes out of gun
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The class definition and associated constants.  
 ************************************************************************/

#ifndef BULLET_H
#define BULLET_H

/**************************************
 * Bullet
 * will create and advance a bullet
 * on the screen.
 **************************************/
class Bullet : public Moveable
{
public:
   Bullet() {}
   void draw()     const;
   void advance();
   void kill();
   void fire(Ship &ship);
};

#endif // BULLET_H
