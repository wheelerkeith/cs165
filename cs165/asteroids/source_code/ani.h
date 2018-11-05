#ifndef ANI_H
#define ANI_H

#include "imageSet.h"
#include "shot.h"
struct aniData
{
    int SetNum;
    int FrDelay;
    float iposx, iposy;
    float velX, velY;
};

class ani
{
public:
	static RECT* pGR;
	imageSet* pimgSet;
	int setNum;
	int frIndex;
	int frDelay;// 1=no delay(normal ani), 2=frAdvance every other time(half ani speed), etc
	int frDelayIndex;
	bool inPlay;

	float posx;
	float posy;
	float velx;
	float vely;
	float szx;
	float szy;

	//** function members **

	void INIT( imageSet* pImgSet, int SetNum, int FrDelay, float iposx, float iposy, float velX, float velY, bool InPlay );

	void move(void);
	void draw( bool frAdvance );
	void drawOffset( bool frAdvance, float offX, float offY );
	bool hitMe(shot& rShot);
	bool split(std::vector<ani>& aVec);// returns true if new rock pushed into aVec

	ani( imageSet* pImgSet, int SetNum, int FrDelay, float iposx, float iposy, float velX, float velY, bool InPlay );
	ani( imageSet* pImgSet, aniData ad, bool InPlay  );
	ani(void);
	~ani(void);
};

#endif
