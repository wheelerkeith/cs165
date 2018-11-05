#ifndef SCENE_H
#define SCENE_H
#include "instance.h"


class Scene
{
private:
	vector<Bird> birds;
	vector<Bullet> bullets;
	Rifle rifle;
	Hud hud;
public:
	Scene();
	void update();
	void draw(); 
}

#endif