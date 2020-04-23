#pragma once
#include "SDL.h"
//#include "data.h"
//#include "fft.h"
#include <stdio.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>
//#include "Jbw_EditBox.h"


#include "Jbw_Frame.h"
//#include "DpGraph.h"



/**************************************************************************************
	CLASS: DataPlot    (Jbw_GUI = JaBberWock Graphical User Interface)
	=============
	This is where all the stuff goes for the Specific GUI that you.
	This is where you BUILD your GUI.
**************************************************************************************/
class Dataplot : public Jbw_Frame{
private:

public:

	SDL_Rect ScreenArea;
	SDL_Rect LogoArea;

	SDL_Window* UserWindow = NULL; // The window we'll be rendering to

	SDL_Surface* wSurf = NULL; // The surface contained by the window
	SDL_Renderer* URender = NULL; // The User window renderer
	SDL_Texture* LogoImage = NULL; //Current displayed texture

	const int U_SCREEN_W = 1100;
	const int U_SCREEN_H = 600;

	/*******************  CONSTRUCTORS  *******************/
	Dataplot();
	~Dataplot();

	/*******************  FUNCTIONS  *******************/
	bool Init(void); // Starts up SDL and creates window
	bool SetupScreen(void);
	void Close(); // Frees media and shuts down SDL
	void UserRender(void);

};