#include "ship.h"

float ship::shotSpeed = 10.0f;

ship::ship(void): pimgSet(NULL){}

ship::ship(imageSet* p_imgSet, int SetG, int SetH, int SetK, float MaxSpeed)
	{
		pimgSet = p_imgSet;
		setG = SetG;
		setH = SetH;
		setK = SetK;
		setNow = setG;
		frIndex = 0;
		inPlay = false;

		posRotate = 0.0f;

		// motion parameters
		maxSpeed = MaxSpeed;
		accel = 0.1f;
		decel = 0.01f;
		chSpeed = false;

		szx = static_cast<float>( pimgSet->pSzx[setG] );
		szy = static_cast<float>( pimgSet->pSzy[setG] );
		sprite.SetImage( pimgSet->img );
		sprite.SetCenter( szx/2.0f, szy/2.0f );
		posx = posy = 0.0f;
		velx = vely = 0.0f;

	}// end of constructor

void ship::INIT(imageSet* p_imgSet, int SetG, int SetH, int SetK, float MaxSpeed, float Accel, float Decel )
	{
		pimgSet = p_imgSet;
		setG = SetG;
		setH = SetH;
		setK = SetK;// for now
		setNow = setG;
		frIndex = 0;

		posRotate = 0.0f;

		// motion parameters
		maxSpeed = MaxSpeed;
		accel = Accel;
		decel = Decel;
		chSpeed = false;

		szx = static_cast<float>( pimgSet->pSzx[setG] );
		szy = static_cast<float>( pimgSet->pSzy[setG] );
		sprite.SetImage( pimgSet->img );
		sprite.SetCenter( szx/2.0f, szy/2.0f );
		posx = posy = 0.0f;
		velx = vely = 0.0f;

	}// end of INIT()

void ship::reset(void)
{
	inPlay = true;
	setNow = setG;
	velx = vely = 0.0f;
	posx = (pGR->left + pGR->right)/2.0f;// center new ship
	posy = (pGR->top + pGR->bottom)/2.0f;
}

ship::~ship(void){}

void ship::draw( bool frAdvance )
	{
		pimgSet->draw( frAdvance, setNow, &frIndex, posx, posy );
		return;
	}// end of draw()

void ship::drawRotate( bool frAdvance )
	{
		const float PI = 3.14159f;
		static int frIdxBoost = 0;

		if( setNow != setK )
		{
		//	pimgSet->drawRotate( &sprite, posRotate, frAdvance, setG, &frIndex, posx, posy );
			pimgSet->drawRotate( &sprite, posRotate, frAdvance, setNow, &frIndex, posx, posy );
			if( chSpeed )
			{
				float ang = posRotate*PI/180.0f;
				pimgSet->drawRotate( &sprite, posRotate, frAdvance, setH, &frIdxBoost, posx-szx*sin(ang)/2.0f, posy-szy*cos(ang)/2.0f );
			}
		}
		else
			pimgSet->drawRotate( &sprite, posRotate, frAdvance, setNow, &frIndex, posx, posy );

		// ship killed
		if( setNow==setK && frAdvance && frIndex==0)
			inPlay = false;

		return;
	}// end of drawRotate()

/*
void ship::drawRotate( bool frAdvance )
	{
		const float PI = 3.14159f;

		pimgSet->drawRotate( &sprite, posRotate, frAdvance, setNow, &frIndex, posx, posy );

		// update posLast
		posxLast = posx;
		posyLast = posy;

		// ship killed
		if(frAdvance && setNow==setK && frIndex==0)
			inPlay = false;

		return;
	}// end of drawRotate()
*/

void ship::move(void)
{
	const float PI = 3.14159f;
	if( chSpeed )
	{
		velx += accel*sin(PI*posRotate/180.0f);
		vely += accel*cos(PI*posRotate/180.0f);
	}
	velx -= decel*velx;// damping
	vely -= decel*vely;

	posx += velx;
	posy += vely;

	// keep ship on screen
	// x-coord
	if( (posx > static_cast<float>(pGR->right)+szx) && (velx > 0.0f) )
		posx = static_cast<float>(pGR->left);
	else if( (posx < static_cast<float>(pGR->left)-szx) && (velx < 0.0f) )
		posx = static_cast<float>(pGR->right);

	// y-coord
	if( (posy > static_cast<float>(pGR->bottom)+szy) && (vely > 0.0f) )
		posy = static_cast<float>(pGR->top);
	else if( (posy < static_cast<float>(pGR->top)-szy) && (vely < 0.0f) )
		posy = static_cast<float>(pGR->bottom);

	return;
}

void ship::fire(shot& rShot)
{
	const float PI = 3.14159f;
	rShot.INIT(posx, posy, shotSpeed*sin(PI*posRotate/180.0f)+velx, shotSpeed*cos(PI*posRotate/180.0f)+vely );
	return;
}

bool ship::hitRock(ani& rAni)
{
	// find square of center to center distance
	float distSq = (posx-rAni.posx-rAni.szx/2.0f)*(posx-rAni.posx-rAni.szx/2.0f) + (posy-rAni.posy-rAni.szy/2.0f)*(posy-rAni.posy-rAni.szy/2.0f);
	if( setNow == setG && distSq < (szx+rAni.szx)*(szx+rAni.szx)/4.0f )
	{
		chSpeed = false;// thruster off
		velx = rAni.velx;// explosion travels
		vely = rAni.vely;// with rock
		setNow = setK;// switch to explosion frame set
		frIndex = 0;// start at 1st frame
		return true;// hit
	}
	return false;// miss
}// end of hitRock()

bool ship::hitShot(shot& rShot)
{
	float distSq = (posx-rShot.posx)*(posx-rShot.posx) + (posy-rShot.posy)*(posy-rShot.posy);
	if( distSq < szx*szx/4.0f )
	{
		chSpeed = false;
		velx = vely = 0.0f;// explosion in place
		setNow = setK;
		frIndex = 0;
		rShot.inAir = false;
		return true;
	}
	else
		return false;
}

bool ship::hitPoint(const float& px, const float py)
{
//	float distSq = (posx+szx/2.0f-px)*(posx+szx/2.0f-px) + (posy+szy/2.0f-py)*(posy+szy/2.0f-py);
	float distSq = (posx-px)*(posx-px) + (posy-py)*(posy-py);
	if( distSq < szx*szx/4.0f )
	{
		setNow = setH;
		return true;
	}
	else
	{
		setNow = setG;
		return false;
	}
}
