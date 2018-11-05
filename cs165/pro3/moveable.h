#include "point.h"


class Instance
{
  private:
   Point position;
   Point velocity;
   int radius;
   bool isDestroyed;
   
  public:
   Instance();
   ~Instance();
   const Point & getPosition() const;
   const Point & getVelocity() const;
   int getRadius();
   void setPosition(Point & position);
   void setVelocity(Point & velocity);
   bool isOustide();
   void update();
   void draw();
   void destroy();
}