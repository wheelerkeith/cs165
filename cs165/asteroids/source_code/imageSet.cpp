#include "imageSet.h"

sf::RenderWindow* imageSet::pWndw = NULL;
sf::Color imageSet::tColor = sf::Color(0,0,0);// transparency mask color

imageSet::imageSet(void)
{
}

imageSet::~imageSet(void)
{
	DLT();
}

bool imageSet::INIT( std::string fileName, int NumSets, int NumCols, int cellSzx, int cellSzy )
	{
		bool OK = FALSE;

		if( !img.LoadFromFile(fileName.c_str()) )
			return false;
		img.CreateMaskFromColor(tColor);
		sprite.SetImage(img);
		wImage = img.GetWidth();
		hImage = img.GetHeight();
		nSets = NumSets;
		cols = NumCols;
		wCell = cellSzx;
		hCell = cellSzy;

		if( (pRowSet = new int[nSets]) )
			if( (pfrCntSet = new int[nSets]) )
				if( (pSzx = new int[nSets]) )
					if( (pSzy = new int[nSets]) )
						OK = TRUE;// all allocations good

		return OK;
	}// end of INIT()

bool imageSet::INIT( std::string fileName )// a text file has been passed
{
    bool OK = FALSE;

    std::ifstream fin( fileName.c_str() );

    if( fin )
    {
        std::string imgFilename;
        std::getline( fin, imgFilename );
        if( !img.LoadFromFile(imgFilename.c_str()) )
            return false;
        img.CreateMaskFromColor(tColor);
        sprite.SetImage(img);
        wImage = img.GetWidth();
        hImage = img.GetHeight();
        fin >> nSets >> cols >> wCell >> hCell;
    }

    if( (pRowSet = new int[nSets]) )
        if( (pfrCntSet = new int[nSets]) )
            if( (pSzx = new int[nSets]) )
                if( (pSzy = new int[nSets]) )
                    OK = TRUE;// all allocations good
    if( OK )
    {
        for( int i = 0; i < nSets; ++i )
            fin >> pRowSet[i] >> pfrCntSet[i] >> pSzx[i] >> pSzy[i];
    }

    return OK;
}// end of INIT()

void imageSet::INITset( const int& setNum, const int& setRowNum, const int& setFrCount, const int& szx, const int& szy )// setNum from zero
	{
		*(pRowSet + setNum) = setRowNum;
		*(pfrCntSet + setNum) = setFrCount;
		*(pSzx + setNum) = szx;
		*(pSzy + setNum) = szy;

		return;
	}// end of INITset()

void imageSet::DLT(void)
	{
		delete [] fileName;

		if( nSets == 1 )
		{
			if( pRowSet != NULL )
				delete pRowSet;
			if( pfrCntSet != NULL )
				delete pfrCntSet;
			if( pSzx != NULL )
				delete pSzx;
			if( pSzy != NULL )
				delete pSzy;
		}
		if( nSets > 1 )
		{
			if( pRowSet != NULL )
				delete []pRowSet;
			if( pfrCntSet != NULL )
				delete []pfrCntSet;
			if( pSzx != NULL )
				delete []pSzx;
			if( pSzy != NULL )
				delete []pSzy;
		}
		return;
	}// end of DLT()

void imageSet::draw( const bool& frAdvance, const int& setNum, int* pfrIndex, const float& posx, const float& posy )
	{
		sf::IntRect srcRect;
		srcRect.Top = (( *pfrIndex / cols ) + pRowSet[setNum])*(hCell+1);
		srcRect.Left = ( *pfrIndex % cols ) * (wCell+1);
		srcRect.Bottom = srcRect.Top  + pSzy[setNum];
		srcRect.Right = srcRect.Left + pSzx[setNum];
		sprite.SetSubRect(srcRect);
		sprite.SetPosition(posx, posy);
		if( pWndw )
			pWndw->Draw( sprite );
		if( frAdvance )
		{
			*pfrIndex += 1;
			if( *pfrIndex >= pfrCntSet[setNum] )
				*pfrIndex = 0;
		}
		return;
	}// end of draw()

void imageSet::drawRotate( sf::Sprite* pSprite, const float& angle, const bool& frAdvance, const int& setNum, int* pfrIndex, const float& posx, const float& posy )
{
		sf::IntRect srcRect;
		srcRect.Top = (( *pfrIndex / cols ) + pRowSet[setNum])*(hCell+1);
		srcRect.Left = ( *pfrIndex % cols ) * (wCell+1);
		srcRect.Bottom = srcRect.Top  + pSzy[setNum];
		srcRect.Right = srcRect.Left + pSzx[setNum];
		pSprite->SetSubRect(srcRect);
		pSprite->SetPosition(posx, posy);
		pSprite->SetRotation( angle );
		if( pWndw )
			pWndw->Draw( *pSprite );
		if( frAdvance )
		{
			*pfrIndex += 1;
			if( *pfrIndex >= pfrCntSet[setNum] )
				*pfrIndex = 0;
		}
		return;
	}// end of drawRotate()

void imageSet::drawCell( const int& setNum, const int& frIndex, const float& posx, const float& posy )
	{
		sf::IntRect srcRect;
		srcRect.Top    = (( frIndex / cols ) + pRowSet[setNum])*(hCell+1);
	    srcRect.Left   = ( frIndex % cols ) * (wCell+1);
		srcRect.Bottom = srcRect.Top  + pSzy[setNum];
	    srcRect.Right  = srcRect.Left + pSzx[setNum];
		sprite.SetSubRect(srcRect);
		sprite.SetPosition(posx, posy);
		if( pWndw )
			pWndw->Draw( sprite );

		return;
	}// end of drawCell()
