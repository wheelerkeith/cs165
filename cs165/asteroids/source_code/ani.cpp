
#include "ani.h"

ani::ani(void){}

ani::~ani(void){}

ani::ani( imageSet* pImgSet, int SetNum, int FrDelay, float iposx, float iposy, float velX, float velY, bool InPlay ):
pimgSet(pImgSet), setNum(SetNum), frDelay(FrDelay), posx(iposx), posy(iposy), velx(velX), vely(velY)
{
	inPlay = InPlay;
	frIndex = 0;
	frDelayIndex = 0;
	if( frDelay < 1)
		frDelay = 1;// ensure min value is held

	if( pimgSet )
	{
		szx = static_cast<float>( pimgSet->pSzx[setNum] );
		szy = static_cast<float>( pimgSet->pSzy[setNum] );
	}
}

ani::ani( imageSet* pImgSet, aniData ad, bool InPlay ):
pimgSet(pImgSet), setNum(ad.SetNum), frDelay(ad.FrDelay), posx(ad.iposx), posy(ad.iposy), velx(ad.velX), vely(ad.velY)
{
	inPlay = InPlay;
	frIndex = 0;
	frDelayIndex = 0;
	if( frDelay < 1)
		frDelay = 1;// ensure min value is held

	if( pimgSet )
	{
		szx = static_cast<float>( pimgSet->pSzx[setNum] );
		szy = static_cast<float>( pimgSet->pSzy[setNum] );
	}
}


void ani::INIT( imageSet* pImgSet, int SetNum, int FrDelay, float iposx, float iposy, float velX, float velY, bool InPlay )
	{
		pimgSet = pImgSet;
		setNum = SetNum;
		frDelay = FrDelay;
		inPlay = InPlay;
		posx = iposx;
		posy = iposy;
		velx = velX;
		vely = velY;
		frIndex = 0;
		if( frDelay < 1)
			frDelay = 1;// ensure min value is held
		frDelayIndex = 0;

	if( pimgSet )
	{
		szx = static_cast<float>( pimgSet->pSzx[setNum] );
		szy = static_cast<float>( pimgSet->pSzy[setNum] );
	}

		return;
	}// end of INIT()

void ani::draw( bool frAdvance )
	{
		if( frAdvance )// advance frDelayIndex and maybe advance frame too
		{
			frDelayIndex++;
			if( frDelayIndex < frDelay )
				frAdvance = FALSE;// draw same frame again
			else
				frDelayIndex = 0;// and do draw next frame
		}
		pimgSet->draw( frAdvance, setNum, &frIndex, posx, posy );
		return;
	}// end of draw()

void ani::drawOffset( bool frAdvance, float offX, float offY )
	{
		if( frAdvance )// advance frDelayIndex and maybe advance frame too
		{
			frDelayIndex++;
			if( frDelayIndex < frDelay )
				frAdvance = FALSE;// draw same frame again
			else
				frDelayIndex = 0;// and do draw next frame
		}
		pimgSet->draw( frAdvance, setNum, &frIndex, posx+offX, posy+offY );
		return;
	}// end of drawOffset()

void ani::move(void)
{
	posx += velx;
	posy += vely;

	// keep ani on screen
	// x-coord
	if( (posx > static_cast<float>(pGR->right) ) && (velx > 0.0f) )
		posx = static_cast<float>(pGR->left) - szx;
	else if( (posx < static_cast<float>(pGR->left)-szx) && (velx < 0.0f) )
		posx = static_cast<float>(pGR->right);

	// y-coord
	if( (posy > static_cast<float>(pGR->bottom) ) && (vely > 0.0f) )
		posy = static_cast<float>(pGR->top) - szy;
	else if( (posy < static_cast<float>(pGR->top)-szy) && (vely < 0.0f) )
		posy = static_cast<float>(pGR->bottom);

	return;
}// end of move()

bool ani::hitMe(shot& rShot)
{
	if( !inPlay )
		return false;

	// find square of distance to center
	float distSq = (posx+szx/2.0f-rShot.posx)*(posx+szx/2.0f-rShot.posx) + (posy+szy/2.0f-rShot.posy)*(posy+szy/2.0f-rShot.posy);
	if( distSq < szx*szx/4.0f )// shot size is neglected here
	{
		rShot.inAir = false;
		return true;
	}
	return false;
}

bool ani::split(std::vector<ani>& aVec)// returns true if new rock pushed into aVec
{
	++setNum;
	if( setNum >= pimgSet->nSets )
	{
		setNum = 0;// safe value
		inPlay = false;
	}
	else// rock splits
	{
		aVec.push_back( ani(pimgSet, setNum, 3, posx, posy, velx-vely, vely+velx, true ) );
		float newVelx = velx + vely;
		vely -= velx;
		velx = newVelx;
		szx = (float)pimgSet->pSzx[ setNum ];
		szy = (float)pimgSet->pSzy[ setNum ];
		return true;
	}
	return false;
}// end of split()
