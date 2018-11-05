#ifndef NUMERICDISPLAY_H
#define NUMERICDISPLAY_H

#include "imageSet.h"

class numericDisplay
{
public:
	imageSet* pimgSet;
	int setNum;
	int base;
	int value;
	int maxValue;
	int maxDigits;
	bool leadZeros;

	float posx;
	float posy;
	float szx;
	float szy;
	float gap;

	// functions

	void draw(void);

	void INIT( imageSet* pImgSet, const int& SetNum, const float& Posx, const float& Posy,
						  const int& MaxDigits, const int& Base, const float& Gap, const bool& LeadZeros );

	numericDisplay(void);
	~numericDisplay(void);
};

#endif
