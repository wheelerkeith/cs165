#include "numericDisplay.h"

numericDisplay::numericDisplay(void)
{
	pimgSet = NULL;
	setNum = 0;

	posx = 0.0f;
	posy = 0.0f;
	maxDigits = 4;
	base = 10;
	gap = 0.0f;
	leadZeros = false;

	value = 0;
	maxValue = base;
	for(int p=1; p<maxDigits; ++p)
		maxValue *= base;
	maxValue -= 1;

	szx = szy = 0.0f;
}

numericDisplay::~numericDisplay(void){}

void numericDisplay::INIT( imageSet* pImgSet, const int& SetNum, const float& Posx, const float& Posy,
						  const int& MaxDigits, const int& Base, const float& Gap, const bool& LeadZeros )
	{
		pimgSet = pImgSet;
		setNum = SetNum;

		posx = Posx;
		posy = Posy;
		maxDigits = MaxDigits;
		base = Base;
		gap = Gap;
		leadZeros = LeadZeros;

		value = 0;
		maxValue = base;
		for(int p=1; p<maxDigits; ++p)
			maxValue *= base;
		maxValue -= 1;

		if( pimgSet )
		{
		//	float fDigits = static_cast<float>( maxDigits );
		//	szx = static_cast<float>( pimgSet->pSzx[setNum]*maxDigits ) + gap*fDigits;
			szx = static_cast<float>( pimgSet->pSzx[setNum] );
			szy = static_cast<float>( pimgSet->pSzy[setNum] );
		}
		else
			szx = szy = 0.0f;

		return;
	}// end of INIT()

void numericDisplay::draw(void)
{
	int dgtIdx = maxDigits - 1;
	int tVal = value;

	while( tVal )
	{
		pimgSet->drawCell( setNum, tVal%base, posx + (float)dgtIdx*(gap+szx), posy );
		--dgtIdx;
		tVal /= base;
	}

	if(leadZeros)
		while( dgtIdx >= 0 )
		{
			pimgSet->drawCell( setNum, 0, posx + (float)dgtIdx*(gap+szx), posy );
			--dgtIdx;
		}

	return;
}// end of draw
