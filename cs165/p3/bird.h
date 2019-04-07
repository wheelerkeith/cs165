/***********************************************************************
 * Header File:
 *    Rifle : A gun
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The class definition and associated constants for a Rifle.  
 ************************************************************************/


#include "moveable.h"


#ifndef BIRD_H
#define BIRD_H

#define BIRD_SIZE 10

class Bird : public Moveable
{
public:
   bool isOutside();
   void respawn();
};

#endif // BIRD_H

#ifndef TOUGH_H
#define TOUGH_H

class Tough : public Bird
{
//   Bird();
   void advance();
   void draw() const;
};

#endif // NORMAL_H

#ifndef NORMAL_H
#define NORMAL_H

class Normal : public Bird
{
//   Bird();
   void advance();
   void draw() const;
};

#endif // NORMAL_H

#ifndef SAFE_H
#define SAFE_H

class Safe : public Bird
{
//   Bird();
   void advance();
   void draw() const;
};

#endif // SAFE_H
