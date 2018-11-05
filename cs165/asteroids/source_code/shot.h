#ifndef SHOT_H
#define SHOT_H

#include "imageSet.h"

class shot
{
public:
	static RECT* pGR;
	static imageSet* pImgSet;
	int setNum;
	int cellNum;

	float posx;
	float posy;
	float velx;
	float vely;
	bool inAir;

	// function
	void move(void);
	void draw(void);
	void INIT(const float& posX, const float& posY, const float& velX, const float& velY );

	shot(void);
	~shot(void);
};

#endif
