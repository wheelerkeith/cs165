#pragma once

#include "ship.h"
#include "asteroid.h"
#include "uiInteract.h"
#include "bullet.h"

#include <vector>
using namespace std;

enum GAME_SATES { IN_PLAY, GAME_OVER };

class Astro
{
public:
   Astro();
   ~Astro();
   
   void processFrame(const Interface *pUI);
   
private:
   Ship			*ship;
   vector<Asteroid> asteroids;
   vector<Bullet> bullets;
   
   void startGame();
   
   void clearAll();
   
   void handleUI(const Interface *pUI);
   void moveItems();
   void drawItems();
   void determineHitAsteroids();
   
   // Ship functions
   void shoot();
   void move();
   
   //Launches random asteroid from container side
   void launchAsteroid();
   //Launches asteroid from specific point
   void launchAsteroid(float x, float y, int size);
   
   void determineLaunchAsteroid();
   
   //Game variables
   int waitCounter;
   int nextLaunchAsteroidTime;
   int state;
   int asteroidVectorSize;
};

