// SFMLwindowsShell.cpp : Defines the entry point for the application.
//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>

#include "ani.h"
#include "badShip.h"
#include "buttonRectDrawn.h"
#include "imageSet.h"
#include "ship.h"
#include "shot.h"
#include "numericDisplay.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

HDC hdc;

RECT GR;

// imageSets
imageSet img_gOne;
imageSet imgBadShips;
imageSet imgShots;
imageSet imgRocks;
imageSet imgDigits;
bool LoadImages(void);

// welcome menu
sf::String welcASTEROIDS;
sf::String welcSelection;
std::vector<sf::String> welcMseStrVec;
std::vector<sf::String> welcKbdStrVec;
sf::String welcEsc;
buttonRectDrawn welcMseButt( 170, 250, 60, 20 );
buttonRectDrawn  welcKbdButt( 500, 250, 60, 20 );
void INITmenuWelcome(void);
void welcMenuDraw( sf::RenderWindow& rApp );
bool welcMenuLogic(void);
void centerString(sf::String& rStr, float Xcenter);
void cycleColor(unsigned& idx, bool& up);// X-code, working great!!
std::vector<ani> welcRockVec;// asteroids on welcome menu

// game over menu
sf::String GameOverStr;
buttonRectDrawn overReplayButt( 370, 300, 60, 20 );
buttonRectDrawn overQuitButt( 370, 350, 60, 20 );
void INITmenuOver(void);
void overMenuDraw( sf::RenderWindow& rApp );
bool overMenuLogic(void);
badShip overBadShip;

// sound clips
sf::SoundBuffer sndBuffFire1;// good ship firing
sf::Sound sndFire1;
sf::SoundBuffer sndBuffFire2;// bad ship firing
sf::Sound sndFire2;
sf::SoundBuffer sndBuffExplode1;// rock/ badship blowup
sf::Sound sndExplode1;
sf::SoundBuffer sndBuffWelcomeBK;// welcome menu BK loop
sf::Sound sndWelcomeBK;
sf::SoundBuffer sndBuffOverBK;// game over menu BK loop
sf::Sound sndOverBK;
bool LoadSounds(void);

// score display
numericDisplay scoreDisplay;

// anis
RECT* ani::pGR = &GR;
std::vector<ani> aniVec;

// ships
ship gOne;
RECT* ship::pGR = &GR;

// badShips
//badShip badOne;
RECT* badShip::pGR = &GR;
ship* badShip::pTarget = &gOne;
std::vector<badShip> badVec;
std::vector<badShip>::iterator itBad;

// shots
RECT* shot::pGR = &GR;
imageSet* shot::pImgSet = &imgShots;
shot shotTemplate1;
int maxShots = 6;
std::vector<shot> shotVec;
const int maxBadShots = 5;
std::vector<shot> badShotVec;

// level data
std::vector< std::vector<aniData> > rockDataMat;
std::vector< std::vector<badShipData> > badShipDataMat;
bool LoadLevelData( std::string fname );

// misc. global vars
int mouse_x = 0;
int mouse_y = 0;
bool mouseControl = false;// false if keyboard control
int rotateNow = 0;// used for keyboard control mode to rotate ship
int rockValues[] = { 100, 200, 300 };
int badShipValue = 1000;
int pointsPerShip = 10000;
float accel = 0.3f, decel = 0.01f, maxSpeed = 10.0f;

bool snap = false;// take a snapshot of screen when 'u' is pressed

// framerate control
bool frAdv = false;
bool paused = false;
bool step = false;// step 1 frame while paused

// level control
const int NumShipsStart = 3;
int shipsLeft = NumShipsStart;// initial # of good ships
int maxLevel = 0;
int levelNum = 0;
unsigned levelDisplayLimit = 100;
unsigned levelDisplayIdx = 0;
sf::String levelNumStr;
char GameState = 'w';// w = welcome menu, g = game in play, 'e' = end (game over) menu

// my functions
void INITshots(void);
void INITlevel(int level);
bool gameLogic(void);
void gameDraw( sf::RenderWindow& rApp );
bool frameTimer(const float& frPeriod);
int hitRocks( std::vector<shot>& shots );// returns score for rocks hit

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char ch = '\0';// for keyboard input
	static bool fired = false;// limit to 1 shot only on spacebar press
	switch(msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN:// gOne accelerates
			switch( GameState )
			{
			case 'g':
				if( mouseControl )
					gOne.chSpeed = true;
				break;
			case 'w':// welcome menu
				if( welcMseButt.hit() || welcKbdButt.hit() )
				{
					if( welcMseButt.hit() )
						mouseControl = true;
					else
						mouseControl = false;

					GameState = 'g';
					levelNum = 0;// 1st level
					INITlevel( levelNum );
					levelDisplayIdx = 0;
					shipsLeft = NumShipsStart;// for level 1 ONLY
					sndWelcomeBK.Stop();
				}
				break;
			case 'e':// game over menu
				if( overReplayButt.hit() )
				{
					sndOverBK.Stop();// stop the over menu BK sound
					sndWelcomeBK.Play();// start the welcome menu BK sound
					for(int i=0; i<maxBadShots; ++i)// reset badShots
						badShotVec.at(i).inAir = false;
					overBadShip.inPlay = false;
					GameState = 'w';
				}
				if( overQuitButt.hit() )
				{
					sndOverBK.Stop();// stop the over menu BK sound
					PostQuitMessage(0);
				}
				break;
			default:
				break;
			}// end switch on GameState

			break;
		case WM_LBUTTONUP:// stop acceleration
			if( mouseControl )
				gOne.chSpeed = false;
			break;
		case WM_RBUTTONDOWN:// fire a shot
			if( GameState == 'g' && mouseControl )
			{
				for(std::vector<shot>::iterator it = shotVec.begin(); it != shotVec.end(); ++it)
					if( it->inAir == false )
					{
						gOne.fire( *it );
						sndFire1.Play();
						break;
					}
			}
			break;
		case WM_MBUTTONDOWN:
			if( mouseControl && (GR.right-GR.left > 100) && (GR.bottom-GR.top > 100) )
			{
				gOne.posx = 50.0f + static_cast<float>( rand()%(GR.right-GR.left-100) );
				gOne.posy = 50.0f + static_cast<float>( rand()%(GR.bottom-GR.top-100) );
			}
			break;
		case WM_MOUSEMOVE:
			button::mseX = LOWORD (lParam);
			button::mseY = HIWORD (lParam);
			break;
		case WM_MOUSEWHEEL:
			if( mouseControl )
			{
				if( GET_WHEEL_DELTA_WPARAM(wParam) > 0 )
					gOne.posRotate += 10.0f;
				else
					gOne.posRotate -= 10.0f;
			}
			break;
		case WM_CHAR:
			ch = (TCHAR)wParam;
			ch = tolower(ch);
			switch( ch )
			{
			case 'p':// pause animation
				paused = !paused;
				break;
			case 's':// step 1 frame while paused
				step = true;
				break;
			case 'r':// reset level play
				INITlevel( levelNum );
				levelDisplayIdx = 0;
				break;
			case 'u':// take a screenshot
				snap = true;
				break;
			case VK_ESCAPE:// Quit
				PostQuitMessage(0);
				break;
			}
			break;
		case WM_KEYDOWN:
			if( GameState == 'g' && !mouseControl && gOne.inPlay && gOne.setNow != gOne.setK )
				switch( wParam )
				{
				case VK_LEFT:// left arrow
					rotateNow = -1;
					break;
				case VK_RIGHT:// right arrow
					rotateNow = 1;
					break;
				case VK_UP:// up arrow
					gOne.chSpeed = true;
					break;
				case VK_DOWN:// down arrow
					if( (GR.right-GR.left > 100) && (GR.bottom-GR.top > 100) )
					{
						gOne.posx = 50.0f + static_cast<float>( rand()%(GR.right-GR.left-100) );
						gOne.posy = 50.0f + static_cast<float>( rand()%(GR.bottom-GR.top-100) );
					}
					break;
				case VK_SPACE:// space bar - fire a shot
					if( !fired )
					{
						for(std::vector<shot>::iterator it = shotVec.begin(); it != shotVec.end(); ++it)
						if( it->inAir == false )
						{
							gOne.fire( *it );
							sndFire1.Play();
							break;
						}
						fired = true;// until spaceber released
					}
					break;
				default:
					break;
				}
			break;
		case WM_KEYUP:
			if( GameState == 'g' && !mouseControl )
				switch( wParam )
				{
				case VK_LEFT:// left arrow
				case VK_RIGHT:// right arrow
					rotateNow = 0;// stop rotating
					break;
				case VK_UP:// up arrow
					gOne.chSpeed = false;// stop boosting
					break;
				case VK_SPACE:// spacebar.
					fired = false;// allow another shot to be fired
					break;
				default:
					break;
				}
			break;
		default:
			return( DefWindowProc(hwnd, msg, wParam, lParam) );
			break;
	}//End Switch on msg.
	return(0);
}//End CALLBACK.

int APIENTRY WinMain(HINSTANCE hinst,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    HWND hwnd;
	MSG  lpmsg;
	memset(&lpmsg,0,sizeof(lpmsg));
	WNDCLASSEX wc = {0};
	static char szAppName[] = "Shell";

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = szAppName;
	wc.hInstance = hinst;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wc.lpszMenuName = 0;
	wc.hbrBackground =  reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.style = CS_GLOBALCLASS;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	if( !RegisterClassEx (&wc) )
		return 0;

    // load level data
	if( !LoadLevelData("levels_config.txt") )
		return 1;
    // load images
	if( !LoadImages() )
		return 2;
	// load sounds
	if( !LoadSounds() )
		return 3;

	// define game window dimensions
	GR.left = 0; GR.right = 800;
	GR.top = 0; GR.bottom = 600;

	// create the main window
    hwnd = CreateWindow(szAppName, "fun2codes Asteroids game", WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX,
		100, 100, 806, 632, NULL, NULL, hinst, NULL);

	// create two SFML views
	DWORD Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
    HWND  View1 = CreateWindow( "STATIC", NULL, Style, 0,  0, 800, 600, hwnd, NULL, hinst, NULL);

	sf::RenderWindow App(View1);

	// initialize the menu variables
	INITmenuWelcome();
	INITmenuOver();
	// load up the shot vectors
	INITshots();
	// start the welcome menu BK sound
	sndWelcomeBK.Play();

	// static class variables
	imageSet::pWndw = &App;
	button::pWndw = &App;
	// local vars
	const float frPeriod = 1.0f/30.0f;// for 30 fps

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	App.UseVerticalSync(true);// default = false

	while( lpmsg.message != WM_QUIT )
	{
		if( PeekMessage( &lpmsg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &lpmsg );
			DispatchMessage( &lpmsg );
		}
        else
		{
			// Game logic at framerate
			if( (frAdv = frameTimer(frPeriod)) )
			{
				switch( GameState )
				{
				case 'g':
					if( !gameLogic() )// game over
					{
						GameState = 'e';
						// stop the level play BK sound here
						sndOverBK.Play();// start the overMenu BK sound here
					}
					break;
				case 'w':
					welcMenuLogic();
					break;
				case 'e':
					overMenuLogic();
					break;
				default:
					break;
				}
			}// end game logic

			// render!
			App.Clear();

			switch( GameState )
			{
			case 'g':
				gameDraw(App);
				break;
			case 'w':
				welcMenuDraw(App);
				break;
			case 'e':
				overMenuDraw(App);
				break;
			default:
				break;
			}

			// save a screenshot when u is pressed
			if ( snap )
			{
				sf::Image Screen = App.Capture();
				Screen.SaveToFile("screenshot.jpg");
				snap = false;
			}

			App.Display();
		}
	}// end of message loop

	UnregisterClass( szAppName, wc.hInstance );

	return(lpmsg.wParam);
 	// TODO: Place code here.
}

// returns false if game over
bool gameLogic(void)
{
	std::vector<shot>::iterator itShot;
	std::vector<ani>::iterator itRock;
	std::vector<ani> newRocksVec;
	static badShip badLast = badVec.back();// save the last one for repeats
	int ptsOver10K = scoreDisplay.value%pointsPerShip;// detect crossing 10000 points multiple

	static bool rocksLeft = false;
	static bool anyBadShots = false;// new
	const int delayCount = 100;
	static int delayIndex = 0;
	static int frIdxLevel = 0;

	// level number display
	if( levelDisplayIdx < levelDisplayLimit )
		++levelDisplayIdx;

	if( gOne.inPlay )
	{
		// ship rotation under keyboard control
		if( !mouseControl && rotateNow != 0 )
		{
			if( rotateNow == 1 )
				gOne.posRotate -= 5.0f;
			else
				gOne.posRotate += 5.0f;
		}
		gOne.move();
	}
	// good shots
	for(itShot = shotVec.begin(); itShot != shotVec.end(); ++itShot)
		if( itShot->inAir )
			itShot->move();
	// bad shots
	if( anyBadShots )// new
	{
		anyBadShots = false;
		for(itShot = badShotVec.begin(); itShot != badShotVec.end(); ++itShot)
			if( itShot->inAir )
			{
				anyBadShots = true;
				itShot->move();
				if( gOne.inPlay )
					if( gOne.hitShot( *itShot ) )
						sndExplode1.Play();
			}
	}
	// badShip
	if( !badVec.empty() )
	{
		// bad ship launching
		++frIdxLevel;
		if( frIdxLevel > itBad->launchTime )
		{
			if( !itBad->inPlay )// one bad ship at a time only
			{
				if( gOne.inPlay && rocksLeft )
					itBad->launch();
				frIdxLevel = 0;// reset
			}
		}
		if( itBad->inPlay )
		{
			itBad->move();
			if( gOne.inPlay )
				if( itBad->fire( badShotVec ) )
				{
					anyBadShots = true;// new
					sndFire2.Play();
				}

			for(itShot = shotVec.begin(); itShot != shotVec.end(); ++itShot)
				if( itShot->inAir )
					if( itBad->hitMe( *itShot ) )
					{
						sndExplode1.Play();
						scoreDisplay.value += badShipValue;
					}
			if( !itBad->inPlay )// it just left/died. Setup for next one
			{
				if( (itBad+1) != badVec.end() )
						++itBad;
				else// else last badShip repeats
					*itBad = badLast;
			}
		}
	}
	// the asteroids
	rocksLeft = false;
	for(itRock = aniVec.begin(); itRock != aniVec.end(); ++itRock)
	{
		if( itRock->inPlay )
		{
			rocksLeft = true;
			itRock->move();
			if( gOne.inPlay )
				if( gOne.hitRock(*itRock) )// rock splits and points are gotten
				{
					sndExplode1.Play();
					scoreDisplay.value += rockValues[itRock->setNum];// score for rock hit
					itRock->split(newRocksVec);
				}

			for(itShot = shotVec.begin(); itShot != shotVec.end(); ++itShot)
				if( itShot->inAir && itRock->hitMe( *itShot ) )
				{
					sndExplode1.Play();
					scoreDisplay.value += 100*(1 + itRock->setNum);// score for rock hit
					itRock->split(newRocksVec);
				}
			if( anyBadShots )// new	- badShots now hit rocks too
				for(itShot = badShotVec.begin(); itShot != badShotVec.end(); ++itShot)
					if( itShot->inAir && itRock->hitMe( *itShot ) )
					{
						sndExplode1.Play();
						itRock->split(newRocksVec);
					}
		}// end if itRock->inPlay
	}// end for each rock
	if( !newRocksVec.empty() )
	{
		for( itRock = newRocksVec.begin(); itRock != newRocksVec.end(); ++itRock )
			aniVec.push_back( *itRock );
		newRocksVec.clear();
	}

	// check if an extra ship was earned
	if( scoreDisplay.value%10000 < ptsOver10K )
		++shipsLeft;// extra ship

	// next level or next ship
	if( !gOne.inPlay || !rocksLeft )
	{
		++delayIndex;
		if( delayIndex > delayCount )
		{
			delayIndex = 0;
			if( !gOne.inPlay )
			{
				--shipsLeft;
				gOne.reset();
				if( shipsLeft < 0 )// Game Over
					return false;
			}
			else// next level
			{
				if( levelNum < maxLevel )
					++levelNum;
				INITlevel( levelNum );
				badLast = badVec.back();
				frIdxLevel = 0;// start countdown to 1st badShip
				levelDisplayIdx = 0;
			}
		}
	}

	return true;
}// end of gameLogic()

int hitRocks( std::vector<shot>& shots )
{
	int score = 0;// retVal
	return score;
}

void gameDraw( sf::RenderWindow& rApp )
{
	std::vector<shot>::iterator itShot;
	std::vector<ani>::iterator itRock;

	// good shots
	for( itShot = shotVec.begin(); itShot != shotVec.end(); ++itShot )
		if( itShot->inAir )
			itShot->draw();
	// bad shots
	for( itShot = badShotVec.begin(); itShot != badShotVec.end(); ++itShot )
		if( itShot->inAir )
			itShot->draw();
	// asteroids
	for( itRock = aniVec.begin(); itRock != aniVec.end(); ++itRock )
		if( itRock->inPlay )
			itRock->draw(frAdv);
	// players ship
	if( gOne.inPlay )
		gOne.drawRotate(frAdv);
	// badShip
	if( !badVec.empty() )
		if( itBad->inPlay )
			itBad->draw(frAdv);
	// score display
	scoreDisplay.draw();
	// ships left display
	for(int s=0; s<shipsLeft; ++s)
		img_gOne.drawCell( 0, 0, 40.0f + (float)s*26.0f, 20.0f );

	// level number display
	if( levelDisplayIdx < levelDisplayLimit )
		rApp.Draw( levelNumStr );

	return;
}// end of gameDraw()

bool frameTimer(const float& frPeriod)
{
	static sf::Clock frClock;
	if( frClock.GetElapsedTime() > frPeriod )
	{
		frClock.Reset();
		if( !paused || step )
		{
			step = false;// only 1 step at a time
			return true;
		}
	}
	return false;
}// end of frameTimer()

bool LoadImages(void)
{
    std::ifstream fin( "bmpImages/list_config_files.txt" );

    if( fin )// parse the 5 file names
    {
        std::string fname;

        std::getline( fin, fname );// name of config. file
        if( !img_gOne.INIT( fname ) ) return false;

        std::getline( fin, fname );
        if( !imgBadShips.INIT( fname ) ) return false;

        std::getline( fin, fname );
        if( !imgRocks.INIT( fname ) ) return false;

        std::getline( fin, fname );
        if( !imgShots.INIT( fname ) ) return false;

        std::getline( fin, fname );
        if( !imgDigits.INIT( fname ) ) return false;

        fin.close();

    }
    gOne.INIT(&img_gOne, 0, 1, 2, maxSpeed, accel, decel );
	gOne.posx = 400.0f;
	gOne.posy = 300.0f;
	gOne.inPlay = true;

	scoreDisplay.INIT( &imgDigits, 0, 650.0f, 20.0f, 6, 10, 2.0f, true );

	return true;
}// end of LoadImages()

bool LoadSounds(void)
{
    std::ifstream fin( "AudioClips/list_audio_files.txt" );

    if( fin )// parse the 5 file names
    {
        std::string fname;

        // gOne firing
        std::getline( fin, fname );
        if( !sndBuffFire1.LoadFromFile( fname.c_str() ) ) return false;
        sndFire1.SetBuffer(sndBuffFire1);
        // badOne firing
        std::getline( fin, fname );
        if( !sndBuffFire2.LoadFromFile( fname.c_str() ) ) return false;
        sndFire2.SetBuffer(sndBuffFire2);
        // all explosions
        std::getline( fin, fname );
        if( !sndBuffExplode1.LoadFromFile( fname.c_str() ) ) return false;
        sndExplode1.SetBuffer(sndBuffExplode1);
        // welcome menu
        std::getline( fin, fname );
        if( !sndBuffWelcomeBK.LoadFromFile( fname.c_str() ) ) return false;
        sndWelcomeBK.SetBuffer( sndBuffWelcomeBK );
        sndWelcomeBK.SetLoop(true);
        // game over menu
        std::getline( fin, fname );
        if( !sndBuffOverBK.LoadFromFile( fname.c_str() ) ) return false;
        sndOverBK.SetBuffer( sndBuffOverBK );
        sndOverBK.SetLoop(true);

        fin.close();
        return true;
    }

	return false;
}// end of LoadSounds()

void INITshots(void)
{

	for(int i=0; i<maxShots; ++i)
		shotVec.push_back(shotTemplate1);
	// badShots
	for(int i=0; i<maxBadShots; ++i)
		badShotVec.push_back(shotTemplate1);

	return;
}// end of INITshots()

bool LoadLevelData( std::string fname )
{
    std::ifstream fin( fname.c_str() );

    std::vector<aniData> aVec;
    std::vector<badShipData> bsVec;

    if( fin )
    {
        // game wide parameters first
        fin >> pointsPerShip >> maxShots >> ship::shotSpeed >> maxSpeed >> accel >> decel;
        fin >> badShipValue >> badShip::shotSpeed;
        fin >> rockValues[0] >> rockValues[1] >> rockValues[2];

        // Now for the level data
        unsigned int Nlevels;
        fin >> Nlevels;
        maxLevel = Nlevels - 1;
        rockDataMat.reserve(Nlevels);
        badShipDataMat.reserve(Nlevels);

        for( unsigned int i =0; i < Nlevels; ++i )
        {
            unsigned int Nrocks;
            fin >> Nrocks;
            aVec.clear();
            aVec.reserve(Nrocks);

            for( unsigned int i =0; i < Nrocks; ++i )
            {
                aniData ad;
                fin >> ad.SetNum >> ad.FrDelay >> ad.iposx >> ad.iposy >> ad.velX >> ad.velY;
                aVec.push_back(ad);
            }
            rockDataMat.push_back(aVec);

            unsigned int Nbaddies;
            fin >> Nbaddies;
            bsVec.clear();
            bsVec.reserve(Nbaddies);

            for( unsigned int i =0; i < Nbaddies; ++i )
            {
                badShipData bsd;
                fin >> bsd.SetG >> bsd.SetK >> bsd.FireInt >> bsd.tLaunch >> bsd.iposx >> bsd.iposy >> bsd.Velx >> bsd.Vely;
                bsVec.push_back(bsd);
            }
            badShipDataMat.push_back(bsVec);
        }

        fin.close();
        return true;
    }

    return false;
}


void INITlevel(int level)
{
	if( !aniVec.empty() )
		aniVec.clear();
	if( !badVec.empty() )
		badVec.clear();

    aniVec.reserve( rockDataMat[level].size() );
	for( unsigned int i = 0; i < rockDataMat[level].size(); ++i )
	    aniVec.push_back( ani(&imgRocks, rockDataMat[level][i], true ) );

    badVec.reserve( badShipDataMat[level].size() );
	for( unsigned int i = 0; i < badShipDataMat[level].size(); ++i )
	    badVec.push_back( badShip( &imgBadShips, &img_gOne, badShipDataMat[level][i] ) );


	itBad = badVec.begin();

	// level number display - modify if maxLevel EVER > 9
	char chStr[10] = "Level ";
	chStr[6] = '0' + levelNum; chStr[7] = '\0';
	levelNumStr.SetText( chStr );
	levelNumStr.SetFont( sf::Font::GetDefaultFont() );
	levelNumStr.SetSize(25.0f);
	levelNumStr.SetColor(sf::Color(255, 0, 0));
	levelNumStr.SetPosition( 300.0f, 40.0f);
	centerString( levelNumStr, 400.0f );

	return;
}// end of INITlevel()

void INITmenuWelcome(void)
{
	welcASTEROIDS.SetText("ASTEROIDS");
	welcASTEROIDS.SetFont( sf::Font::GetDefaultFont() );
	welcASTEROIDS.SetSize(50.f);
	welcASTEROIDS.SetColor(sf::Color(0, 0, 255));
	welcASTEROIDS.SetPosition( 300.0f, 100.0f);
	centerString( welcASTEROIDS, 400.0f );

	welcSelection.SetText("select control mode");
	welcSelection.SetFont( sf::Font::GetDefaultFont() );
	welcSelection.SetSize(25.f);
	welcSelection.SetColor(sf::Color(255, 255, 255));
	welcSelection.SetPosition( 350.0f, 200.0f);
	centerString( welcSelection, 400.0f );

	sf::String tempStr;
	for(int i=0; i<5; ++i)
	{
		tempStr.SetFont( sf::Font::GetDefaultFont() );
		tempStr.SetSize(15.f);
		tempStr.SetColor(sf::Color(255, 0, 0));
		tempStr.SetPosition( 150.0f, 280.0f + 20.0f*(float)i );
		welcMseStrVec.push_back( tempStr );
	}
	welcMseStrVec.at(0).SetText("Left     thrust");
	welcMseStrVec.at(1).SetText("Right    fire");
	welcMseStrVec.at(2).SetText("wheel");
	welcMseStrVec.at(3).SetText("scroll   rotate ship");
	welcMseStrVec.at(4).SetText("click    hyperjump");

	for(int i=0; i<5; ++i)
	{
		tempStr.SetFont( sf::Font::GetDefaultFont() );
		tempStr.SetSize(15.f);
		tempStr.SetColor(sf::Color(255, 0, 0));
		tempStr.SetPosition( 450.0f, 280.0f + 20.0f*(float)i );
		welcKbdStrVec.push_back( tempStr );
	}
	welcKbdStrVec.at(0).SetText("Up arrow           thrust");
	welcKbdStrVec.at(1).SetText("Spacebar           fire");
	welcKbdStrVec.at(2).SetText("left/right arrow   rotate ship");
	welcKbdStrVec.at(3).SetText("down arrow         hyperjump");

	welcEsc.SetText("Esc = Quit");
	welcEsc.SetFont( sf::Font::GetDefaultFont() );
	welcEsc.SetSize(25.f);
	welcEsc.SetColor(sf::Color(0, 255, 0));
	welcEsc.SetPosition( 370.0f, 500.0f);
	centerString( welcEsc, 400.0f );

	welcMseButt.INITlabel( "mouse", 14, sf::Color(255,255,255), 'c' );
	welcMseButt.unSelColor = sf::Color(0, 0, 255);
	welcMseButt.unMoColor = sf::Color(255, 0, 0);
	welcKbdButt.INITlabel( "keyboard", 14, sf::Color(255,255,255), 'c' );
	welcKbdButt.unSelColor = sf::Color(0, 0, 255);
	welcKbdButt.unMoColor = sf::Color(255, 0, 0);

	// some asteroids flying around
	welcRockVec.push_back( ani(&imgRocks, 1, 4, 200.0f, GR.bottom+100.0f, 0.3f, -1.4f, true) );// bottom left
	welcRockVec.push_back( ani(&imgRocks, 0, 4, 600.0f, GR.bottom+100.0f, -1.3f, -1.0f, true) );// bottom right
	welcRockVec.push_back( ani(&imgRocks, 0, 4, GR.left-80.0f, 200.0f, 1.0f, 1.2f, true ) );// left
	welcRockVec.push_back( ani(&imgRocks, 1, 4, GR.right+20.0f, 100.0f, -1.0f, 1.0f, true ) );// right
	welcRockVec.push_back( ani(&imgRocks, 0, 4, 500.0f, GR.top-100.0f, 0.6f, 2.0f, true ) );// top

return;
}// end of void INITmenuWelcome()

void welcMenuDraw( sf::RenderWindow& rApp )
{
	for( std::vector<ani>::iterator itRock = welcRockVec.begin(); itRock != welcRockVec.end(); ++itRock )
		itRock->draw(frAdv);

	rApp.Draw( welcASTEROIDS );
	rApp.Draw( welcSelection );
	rApp.Draw( welcEsc );

	std::vector<sf::String>::iterator itStr;
	for( itStr = welcMseStrVec.begin(); itStr != welcMseStrVec.end(); ++itStr )
		rApp.Draw( *itStr );
	for( itStr = welcKbdStrVec.begin(); itStr != welcKbdStrVec.end(); ++itStr )
		rApp.Draw( *itStr );

	welcMseButt.draw();
	welcKbdButt.draw();

	return;
}// end of welcMenuDraw()

bool welcMenuLogic(void)
{
	static unsigned bluIdx = 255;
	static bool bluUp = false;
	cycleColor(bluIdx, bluUp);

	static unsigned grnIdx = 0;
	static bool grnUp = true;
	cycleColor(grnIdx, grnUp);

	// ASTEROIDS string color varies
	welcASTEROIDS.SetColor(sf::Color(0, grnIdx, bluIdx));
	// the buttons
	welcMseButt.mseOver();
	welcKbdButt.mseOver();
	// some rocks
	for( std::vector<ani>::iterator itRock = welcRockVec.begin(); itRock != welcRockVec.end(); ++itRock )
		itRock->move();

	return true;
}// end of welcMenuLogic()

void cycleColor(unsigned& idx, bool& up)
{
	if(up)
	{
		++idx;
		if(idx == 255)
			up = false;
		return;
	}
	else
	{
		--idx;
		if(idx == 0)
			up = true;
		return;
	}
}

void INITmenuOver(void)
{
	GameOverStr.SetText("GAME OVER");
	GameOverStr.SetFont( sf::Font::GetDefaultFont() );
	GameOverStr.SetSize(50.f);
	GameOverStr.SetColor(sf::Color(255, 0, 0));
	GameOverStr.SetPosition( 300.0f, 150.0f);
	centerString( GameOverStr, 400.0f );

	overReplayButt.INITlabel( "Replay", 14, sf::Color(255, 255, 255), 'c' );
	overReplayButt.unSelColor = sf::Color(0, 0, 255);
	overReplayButt.unMoColor = sf::Color(255, 0, 0);
	overQuitButt.INITlabel( "Quit", 14, sf::Color(255, 255, 255), 'c' );
	overQuitButt.unSelColor = sf::Color(0, 0, 255);
	overQuitButt.unMoColor = sf::Color(255, 0, 0);

	// badShip
	overBadShip.INIT( &imgBadShips, 0, &img_gOne, 2, 50 );
	overBadShip.launchTime = 200;
	overBadShip.posx = -50.0f;
	overBadShip.posy = 100.0f;
	overBadShip.velx = 5.0f;

	return;
}// end of INITmenuOver()

void overMenuDraw( sf::RenderWindow& rApp )
{
	rApp.Draw( GameOverStr );
	overReplayButt.draw();
	overQuitButt.draw();

	// bad ship
	if( overBadShip.inPlay )
		overBadShip.draw(frAdv);
	for(std::vector<shot>::iterator itShot = badShotVec.begin(); itShot != badShotVec.end(); ++itShot)
		if( itShot->inAir )
			itShot->draw();

	return;
}// end of overMenuDraw()

bool overMenuLogic(void)// returns true if replay
{
	static int launchIndex = overBadShip.launchTime - 30;

	overReplayButt.mseOver();
	overQuitButt.mseOver();

	// badShip
	++launchIndex;
	if( launchIndex > overBadShip.launchTime )
	{
		overBadShip.posx = -50.0f;
		overBadShip.posy = 100.0f;
		overBadShip.launch();
		launchIndex = 0;
	}
	if( overBadShip.inPlay )
	{
		gOne.posx = static_cast<float>( button::mseX );
		gOne.posy = static_cast<float>( button::mseY );
		overBadShip.move();
		if( overBadShip.fire( badShotVec ) ) sndFire2.Play();
	}
	for(std::vector<shot>::iterator itShot = badShotVec.begin(); itShot != badShotVec.end(); ++itShot)
		if( itShot->inAir )
			itShot->move();

	return false;
}// end of overMenuLogic()

void centerString(sf::String& rStr, float Xcenter)
{
	sf::FloatRect strRect = rStr.GetRect();
	float len = strRect.Right - strRect.Left;
	rStr.SetX( Xcenter - len/2.0f );
	return;
}
