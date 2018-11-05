/****************************************
 * Astro game
 ***************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "astro.h"
using namespace std;

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
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
 * Main is pretty sparse.  Just initialize
 * my ball type and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Astro");    // initialize OpenGL
   Astro game;                           // initialize the game state
   ui.run(callBack, &game);             // set everything into action

   return 0;
}
