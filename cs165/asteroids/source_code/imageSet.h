#ifndef IMAGESET_H
#define IMAGESET_H

#include <SFML/Graphics.hpp>
#include<string>
#include<fstream>

class imageSet
{
public:
	static sf::RenderWindow* pWndw;
	static sf::Color tColor;// transparency mask color
	sf::Image img;
	sf::Sprite sprite;
	char* fileName;// new
	int wImage;
	int hImage;
	int cols;// # of columns in which frames are stored on surface
	int wCell;// dimensions of each cell = constant across surface
	int hCell;// one frame is stored in each cell

	//** for dynamic allocation of 4 arrays **
	int nSets;// # elements of each array = # of frame sets stored on surface

	int* pRowSet;// array#1: row# in which frame set begins
	int* pfrCntSet;// array#2: #frames in set
	int* pSzx;// array#3,4: in case images smaller than wCell x hCell are stored this row
	int* pSzy;

	// functions
	void draw( const bool& frAdvance, const int& setNum, int* pfrIndex, const float& posx, const float& posy );
	void drawRotate( sf::Sprite* pSprite, const float& angle, const bool& frAdvance, const int& setNum, int* pfrIndex, const float& posx, const float& posy );
	void drawCell( const int& setNum, const int& frIndex, const float& posx, const float& posy );

	bool INIT( std::string fileName, int NumSets, int NumCols, int cellSzx, int cellSzy );
	bool INIT( std::string fileName );

	// INITs one set - first is setNum=0
	void INITset( const int& setNum, const int& setRowNum, const int& setFrCount, const int& szx, const int& szy );// setNum from zero


	void DLT(void);

	imageSet(void);
	~imageSet(void);
};

#endif
