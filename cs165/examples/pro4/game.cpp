/****************************************
 * Astro game
 ***************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "astro.h"
using namespace std;

/*************************************
 * Creates a game pointer and then calls
 * the processFrame function
 **************************************/
void callBack(const Interface *pUI, void * p)
{
   Astro * pAstro = (Astro *)p;  // cast the void pointer into a known type
   
   pAstro->processFrame(pUI);
   
}

// set the bounds of the drawing rectangle
float Point::xMin = -300.0;
float Point::xMax =  300.0;
float Point::yMin = -300.0;
float Point::yMax =  300.0;

/*********************************
 * Main initializes the game
 * and calls the display engine.
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Asteroids");    // initialize OpenGL
   Astro game;                           // initialize the game state
   ui.run(callBack, &game);             // set everything into action

   return 0;
}
