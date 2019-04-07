#include "astro.h"
#include "uiDraw.h"
#include "asteroid.h"
#include <cmath>
#include <stdlib.h>

#define ASTEROID_BIG_RADIUS 10
#define ASTEROID_MEDIUM_RADIUS 6
#define ASTEROID_LITTLE_RADIUS 3


Astro::Astro() : waitCounter(0), nextLaunchAsteroidTime(0), state(IN_PLAY)
{
   startGame();
}

// ************************************************************************
Astro::~Astro()
{
   clearAll();
}

// ************************************************************************
void Astro::processFrame(const Interface *pUI)
{
   static int gameOverCounter = 0;
   switch (state)
   {
      case IN_PLAY:
         // Handle UI
         handleUI(pUI);
         
         //Create asteroids if time permits
         determineLaunchAsteroid();
         
         // Move items
         moveItems();
         
         determineHitAsteroids();
         
         // Draw stuff
         drawItems();
         
         gameOverCounter = 0;
         break;
      case GAME_OVER:
         drawText(Point(), "GAME OVER");
         if (gameOverCounter == 0)
         {
            clearAll();
            startGame();
         }
         else if (gameOverCounter >= 50)
         {
            state = IN_PLAY;
         }
         gameOverCounter++;
         break;
      default:
         break;
   }
   this->waitCounter++;
}

float distance(float dX0, float dY0, float dX1, float dY1)
{
   return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

void Astro::determineHitAsteroids()
{
   //Determine if bullets hit any asteroids
   for (int i = 0; i < bullets.size(); i++)
   {
      for (int j = 0; j < asteroids.size(); j++)
      {
         if (distance(bullets[i].getX(), bullets[i].getY(), asteroids[j].getX(), asteroids[j].getY()) <= (bullets[i].getRadius() +
                                                                                                          asteroids[j].getRadius()))
         {
            //Split up big asteroids
            if (asteroids[j].getRadius() == ASTEROID_BIG_RADIUS)
            {
               launchAsteroid(asteroids[j].getX(), asteroids[j].getY(), ASTEROID_MEDIUM_RADIUS);
               launchAsteroid(asteroids[j].getX(), asteroids[j].getY(), ASTEROID_MEDIUM_RADIUS);
            }
            else if (asteroids[j].getRadius() == ASTEROID_MEDIUM_RADIUS)
            {
               launchAsteroid(asteroids[j].getX(), asteroids[j].getY(), ASTEROID_LITTLE_RADIUS);
               launchAsteroid(asteroids[j].getX(), asteroids[j].getY(), ASTEROID_LITTLE_RADIUS);
               launchAsteroid(asteroids[j].getX(), asteroids[j].getY(), ASTEROID_LITTLE_RADIUS);
            }
            asteroids.erase(asteroids.begin() + j);
            bullets.erase(bullets.begin() + i);
            break;
         }
      }
   }
   
   //Determine if ship is hit or not
   for (int j = 0; j < asteroids.size(); j++)
   {
      if (distance(ship->getX(), ship->getY(), asteroids[j].getX(), asteroids[j].getY()) <= (10 + asteroids[j].getRadius()))
      {
         state = GAME_OVER;
      }
   }
}

// *************************************************************************** 
void Astro::handleUI(const Interface *pUI)
{
   if (pUI->isRight())
      ship->rotateRight();

   if (pUI->isLeft())
      ship->rotateLeft();

   if ((pUI->isUp() || pUI->isSpace()) && (pUI->isSpace() % 5 == 0 || pUI->isSpace() == 1))
      shoot();

   if (pUI->isDown())
   {
      ship->accelerate();
   }
}

// ********     ******************************************************************* 
void Astro::moveItems()
{
   // Ship
   ship->move();

   //Bullets
   if (!bullets.empty())
   {
      if (bullets[0].isReadyToDie())
      {
         bullets.erase(bullets.begin());
      }
   }
   for (int i = 0; i < bullets.size(); i++)
   {
      bullets[i].moveBullet();
   }
   
   
   //Asteroids
   vector<int> asteroidsToDelete;
   for (int i = 0; i < asteroids.size(); i++)
   {
      asteroids[i].move();
      if (asteroids[i].isReadyToDie())
      {
         asteroidsToDelete.push_back(i);
         asteroids[i].getVelocity();//.resurrect();
      }
   }
   
   for (int i = 0; i < asteroidsToDelete.size(); i++)
   {
      asteroids.erase(asteroids.begin() + asteroidsToDelete[i] - i);
   }
}

// *************************************************************************** 
void Astro::drawItems()
{
   // Draw Ship
   ship->draw();
   
   // Draw Bullets
   for (int i = 0; i < bullets.size(); i++)
   {
      bullets[i].draw();
   }
   
   // Draw Rocks
   for (int i = 0; i < asteroidVectorSize; i++)
   {
      asteroids[i].draw();
   }
}

// ************************************************************************
void Astro::clearAll()
{
   // Delete the ship
   delete ship;
   
   asteroids.clear();
   bullets.clear();
}

// ************************************************************************
void Astro::startGame()
{
   // Create ship in the centre
   ship = new Ship(0, 0, 0, 0);
}

// *************************************************************************** 
void Astro::shoot()
{
   int x = this->ship->getTip().getX();
   int y = this->ship->getTip().getY();
   float dx = this->ship->getDX() * 2;
   float dy = this->ship->getDY() * 2;
   
   //Randomly set one of the axis to max so that it comes onto the screen
   static int id;
   this->bullets.push_back(Bullet(x, y, dx, dy, this->ship->getRotation()));
}

// *************************************************************************** 
void Astro::move()
{
   ship->move();
}


void Astro::launchAsteroid()
{
   float x = rand() % (int)Point::xMax + 1;
   float y = rand() % (int)Point::yMax + 1;
   float size;
   //Randomly set one of the axis to max so that it comes onto the screen.  Also random size between medium or big.
   if (x > y)
   {
      x = (int)Point::xMax * pow(-1, (int)(rand() % 2 + 1));
      size = ASTEROID_BIG_RADIUS;
   }
   else
   {
      y = (int)Point::yMax * pow(-1, (int)(rand() % 2 + 1));
      size = ASTEROID_MEDIUM_RADIUS;
   }
   launchAsteroid(x, y, size);
}

void Astro::launchAsteroid(float x, float y, int size)
{
   int dxN = 1;
   int dyN = 1;
   if (x > 0)
   {
      dxN = -1;
   }
   if (y > 0)
   {
      dyN = -1;
   }
   tempdy = (rand() % 2 + 1.0) * dyN;
   tempdx = (rand() % 2 + 1.0) * dxN;
   static int id;
   this->asteroids.push_back(Asteroid(x, y, tempdx, tempdy, id++));
   asteroidVectorSize++;
}


void Astro::determineLaunchAsteroid()
{
   if (waitCounter >= nextLaunchAsteroidTime)
   {
      launchAsteroid();
      int randNum = rand() % 100;
      nextLaunchAsteroidTime += randNum;
   }
}
