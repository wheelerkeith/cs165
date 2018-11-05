#ifndef BADSHIP_H
#define BADSHIP_H

#include "imageSet.h"
#include "shot.h"
#include "ship.h"

struct badShipData
{
    int SetG, SetK;
    int FireInt;
    int tLaunch;
    float iposx, iposy;
    float Velx, Vely;
};

class badShip
{
public:
	float szx;
	float szy;
	float posx;
	float posy;
	float velx;
	float vely;

	static RECT* pGR;
	static ship* pTarget;// pointer to gOne so badShip can aim shots
	static float shotSpeed;
	bool inPlay;// ship is alive
	int launchTime;

	imageSet* pimgSetNow;// containing all ship image frames (normal, hit and kill)
	imageSet* pimgSetG;
	imageSet* pimgSetK;
	int frIndex;// ani. index
	int setNow;// current set is one of 3 below
	int setG;// set for normal frames
	int setK;// hit-ani frames
	int fireInt;// firing interval in frames
	int	fireIntIdx;

	// functions
	void INIT(imageSet* p_imgSetG, int SetG, imageSet* p_imgSetK, int SetK, int FireInt );
	void launch( void );//const float& Posx, const float& Posy, const float& Velx, const float& Vely );
	void draw( bool frAdvance );
	void move(void);
	bool hitMe(shot& rShot);
	bool fire( std::vector<shot>& rShotVec );

	badShip(imageSet* p_imgSetG, int SetG, imageSet* p_imgSetK, int SetK, int FireInt, int tLaunch,
                float iposx, float iposy, float Velx, float Vely );
    badShip(imageSet* p_imgSetG, imageSet* p_imgSetK,  badShipData bs );

	badShip(void);
	~badShip(void);
};

#endif
