#include "badShip.h"

float badShip::shotSpeed = 10.0f;

badShip::badShip(void): pimgSetNow(NULL), pimgSetG(NULL), pimgSetK(NULL){}

badShip::badShip(imageSet* p_imgSetG, int SetG,imageSet* p_imgSetK, int SetK, int FireInt, int tLaunch,
                float iposx, float iposy, float Velx, float Vely )
{
	pimgSetG = p_imgSetG;
    pimgSetK = p_imgSetK;
    pimgSetNow = p_imgSetG;
	setG = SetG;
	setK = SetK;// for now
	setNow = setG;
	fireInt = FireInt;
	launchTime = tLaunch;
	fireIntIdx = 0;
	frIndex = 0;
	inPlay = false;

	velx = Velx;
	vely = Vely;
	posx = iposx;
	posy = iposy;

	szx = static_cast<float>( pimgSetG->pSzx[setG] );
	szy = static_cast<float>( pimgSetG->pSzy[setG] );
}

badShip::badShip( imageSet* p_imgSetG, imageSet* p_imgSetK, badShipData bs )
{
	pimgSetG = p_imgSetG;
    pimgSetK = p_imgSetK;
    pimgSetNow = p_imgSetG;
	setG = bs.SetG;
	setK = bs.SetK;// for now
	setNow = setG;
	fireInt = bs.FireInt;
	launchTime = bs.tLaunch;
	fireIntIdx = 0;
	frIndex = 0;
	inPlay = false;

	velx = bs.Velx;
	vely = bs.Vely;
	posx = bs.iposx;
	posy = bs.iposy;

	szx = static_cast<float>( pimgSetG->pSzx[setG] );
	szy = static_cast<float>( pimgSetG->pSzy[setG] );
}

badShip::~badShip(void){}

void badShip::INIT(imageSet* p_imgSetG, int SetG, imageSet* p_imgSetK, int SetK, int FireInt )
	{
		pimgSetG = p_imgSetG;
		pimgSetK = p_imgSetK;
		pimgSetNow = p_imgSetG;
		setG = SetG;
		setK = SetK;// for now
		setNow = setG;
		fireInt = FireInt;
		fireIntIdx = 0;
		frIndex = 0;
		inPlay = false;

		velx = vely = 0.0f;
		posx = posy = 0.0f;

		szx = static_cast<float>( pimgSetG->pSzx[setG] );
		szy = static_cast<float>( pimgSetG->pSzy[setG] );


	}// end of INIT()

// call to launch ship after INIT
void badShip::launch( void )//const float& Posx, const float& Posy, const float& Velx, const float& Vely )
	{
		setNow = setG;
		pimgSetNow = pimgSetG;
		frIndex = 0;
		fireIntIdx = 0;
		inPlay = true;

	}// end of INIT()

void badShip::draw( bool frAdvance )
	{
		pimgSetNow->draw( frAdvance, setNow, &frIndex, posx, posy );
		return;
	}// end of draw()

void badShip::move(void)
{
	posx += velx;
	posy += vely;

	// ship is gone when it leaves the screen
	// x-coord
	if( (velx >= 0.0f) && (posx > static_cast<float>(pGR->right) ) )
	{
		inPlay = false;
		return;
	}
	if( (velx < 0.0f) && (posx < static_cast<float>(pGR->left)-szx) )
	{
		inPlay = false;
		return;
	}

	// y-coord
	if( (vely >= 0.0f) && (posy > static_cast<float>(pGR->bottom)+szy) )
	{
		inPlay = false;
		return;
	}
	if( (vely < 0.0f) && (posy < static_cast<float>(pGR->top)-szy) )
	{
		inPlay = false;
		return;
	}
	if( setNow==setK && frIndex==0)
	{
	    pimgSetNow = pimgSetG;
	    setNow = setG;
		inPlay = false;
	}

	return;
}// end of move()

bool badShip::hitMe(shot& rShot)
{
	float distSq = (posx+szx/2.0f-rShot.posx)*(posx+szx/2.0f-rShot.posx) + (posy+szy/2.0f-rShot.posy)*(posy+szy/2.0f-rShot.posy);
	if( distSq < szx*szx/4.0f && setNow == setG )// shot size is neglected here
	{
		rShot.inAir = false;
		setNow = setK;
		pimgSetNow = pimgSetK;
		frIndex = 0;
		velx = vely = 0.0f;
		return true;
	}
	return false;
}

bool badShip::fire( std::vector<shot>& rShotVec )
{
	if( !pTarget )
		return false;

	++fireIntIdx;
	if( fireIntIdx >= fireInt )
	{
		fireIntIdx = 0;
		if( setNow == setK )return false;// don't fire efter being hit
		for( std::vector<shot>::iterator itShot = rShotVec.begin(); itShot != rShotVec.end(); ++itShot )
		{
			if( !itShot->inAir )
			{
				float dx = pTarget->posx - posx;
				float dy = pTarget->posy - posy;
				float dist = sqrt( dx*dx + dy*dy );
				itShot->INIT(posx, posy, shotSpeed*dx/dist, shotSpeed*dy/dist );
				return true;
			}
		}
	}
	return false;
}// end of fire()

