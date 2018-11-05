#ifndef SHIP_H
#define SHIP_H

#include <cmath>
#include "imageSet.h"
#include "shot.h"
#include "ani.h"
//#define PI 3.14159f

class ship
{
public:
	float szx;
	float szy;
	float posx;
	float posy;
	float velx;
	float vely;
	float posRotate;// angular orientation given by user input

	// motion parameters
	static RECT* pGR;
	static float shotSpeed;
	float maxSpeed;
	float accel, decel;
	bool chSpeed;// set true by event and false when speed == targetSpeed
	bool inPlay;// ship is alive

	imageSet* pimgSet;// containing all ship image frames (normal, hit and kill)
	sf::Sprite sprite;// so each ship rotates independent of another
	int frIndex;// ani. index
	int setNow;// current set is one of 3 below
	int setG;// set for normal frames
	int setH;// hit-ani frames
	int setK;// hit-ani frames

	// functions

	void draw( bool frAdvance );
	void drawRotate( bool frAdvance );
	void move(void);
	void fire(shot& rShot);
	bool hitRock(ani& rAni);
	bool hitShot(shot& rShot);
	bool hitPoint(const float& px, const float py);// for testing
	void reset(void);// prepares next ship
	void INIT(imageSet* p_imgSet, int SetG, int SetH, int SetK, float MaxSpeed, float Accel, float Decel );// mirrors constructor

	ship(void);
	ship(imageSet* p_imgSet, int SetG, int SetH, int SetK, float MaxSpeed);
	~ship(void);
};

#endif
